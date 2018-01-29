/* -MODULE----------------------------------------------------------------------
Phorward Foundation Toolkit
Copyright (C) 2006-2018 by Phorward Software Technologies, Jan Max Meyer
http://www.phorward-software.com ++ contact<at>phorward<dash>software<dot>com
All rights reserved. See LICENSE for more information.

File:	gram.c
Usage:	Grammar construction and preparation.
----------------------------------------------------------------------------- */

#include "phorward.h"

/** Prepares the grammar //g// by computing all necessary stuff required for
runtime and parser generator.

The preparation process includes:
- Setting up final symbol and productions IDs
- Nonterminals FIRST-set computation
- Marking of left-recursions
- The 'lexem'-flag pull-through the grammar.
-

This function is only run internally.
Don't call it if you're unsure ;)... */
pboolean pp_gram_prepare( ppgram* g )
{
	plistel*		e;
	plistel*		er;
	plistel*		ep;
	ppprod*			prod;
	ppprod*			cprod;
	ppsym*			sym;
	pboolean		nullable;
	plist*			call;
	plist*			done;
	int				i;
	int				cnt;
	int				pcnt;
	unsigned int	idx;

	if( !g )
	{
		WRONGPARAM;
		return FALSE;
	}

	if( !g->goal )
	{
		/* No such goal! */
		return FALSE;
	}

	/* Reset symbols */
	for( idx = 0, e = plist_first( g->symbols ); e; e = plist_next( e ), idx++ )
	{
		sym = (ppsym*)plist_access( e );
		sym->idx = idx;

		if( PPSYM_IS_TERMINAL( sym ) )
		{
			if( !plist_first( sym->first ) )
				plist_push( sym->first, sym );
		}
		else
			plist_erase( sym->first );
	}

	/* Reset productions */
	for( idx = 0, e = plist_first( g->prods ); e; e = plist_next( e ), idx++ )
	{
		prod = (ppprod*)plist_access( e );
		prod->idx = idx;
	}

	/* Compute FIRST sets and mark left-recursions */
	cnt = 0;
	call = plist_create( 0, PLIST_MOD_PTR | PLIST_MOD_RECYCLE );
	done = plist_create( 0, PLIST_MOD_PTR | PLIST_MOD_RECYCLE );

	do
	{
		pcnt = cnt;
		cnt = 0;

		plist_for( g->prods, e )
		{
			cprod = (ppprod*)plist_access( e );
			plist_push( call, cprod );

			while( plist_pop( call, &prod ) )
			{
				plist_push( done, prod );

				plist_for( prod->rhs, er )
				{
					sym = (ppsym*)plist_access( er );

					nullable = FALSE;

					if( PPSYM_IS_NONTERMINAL( sym ) )
					{
						/* Union first set */
						plist_union( cprod->lhs->first, sym->first );

						/* Put prods on stack */
						for( i = 0; ( prod = pp_sym_getprod( sym, i ) ); i++ )
						{
							if( plist_count( prod->rhs ) == 0 )
							{
								nullable = TRUE;
								continue;
							}

							if( prod == cprod )
							{
								prod->lhs->flags |= PPFLAG_LEFTREC;
								prod->flags |= PPFLAG_LEFTREC;
							}
							else if( !plist_get_by_ptr( done, prod ) )
								plist_push( call, prod );
						}
					}
					/* Extend first set if required */
					else if( !plist_get_by_ptr( cprod->lhs->first, sym ) )
						plist_push( cprod->lhs->first, sym );

					if( !nullable )
						break;
				}

				/* Flag nullable */
				if( !er )
				{
					cprod->flags |= PPFLAG_NULLABLE;
					cprod->lhs->flags |= PPFLAG_NULLABLE;
				}

				cnt += plist_count( cprod->lhs->first );
			}

			plist_erase( done );
		}
	}
	while( pcnt < cnt );

	plist_clear( call );
	plist_clear( done );

	/* Pull-through all lexem symbols */
	plist_for( g->symbols, e )
	{
		sym = (ppsym*)plist_access( e );

		if( PPSYM_IS_TERMINAL( sym ) || !( sym->flags & PPFLAG_LEXEM ) )
			continue;

		plist_push( call, sym );
	}

	while( plist_pop( call, &sym ) )
	{
		plist_push( done, sym );

		for( i = 0; ( prod = pp_sym_getprod( sym, i ) ); i++ )
		{
			plist_for( prod->rhs, er )
			{
				sym = (ppsym*)plist_access( er );
				sym->flags |= PPFLAG_LEXEM;

				if( PPSYM_IS_NONTERMINAL( sym ) )
				{
					if( !plist_get_by_ptr( done, sym )
						&& !plist_get_by_ptr( call, sym ) )
						plist_push( call, sym );
				}
			}
		}
	}

	/* Clear all lists */
	plist_free( call );
	plist_free( done );

	g->flags |= PPFLAG_FINALIZED;
	return TRUE;
}

/** Creates a new ppgram-object. */
ppgram* pp_gram_create( void )
{
	ppgram*		g;

	g = (ppgram*)pmalloc( sizeof( ppgram ) );

	g->symbols = plist_create( sizeof( ppsym ), PLIST_MOD_RECYCLE
													| PLIST_MOD_EXTKEYS
														| PLIST_MOD_UNIQUE );
	g->prods = plist_create( sizeof( ppprod ), PLIST_MOD_RECYCLE );

	g->eof = pp_sym_create( g, PPSYM_T_EOF, PPFLAG_SPECIAL );

	return g;
}


#define NAMELEN			80
#define DERIVCHAR		'\''


static pboolean traverse_production( ppgram* g, ppsym* lhs, ppast* node );

/* Derive name from basename */
static char* derive_name( ppgram* g, char* base )
{
	int             i;
	static
	char    deriv   [ ( NAMELEN * 2 ) + 1 ];

	sprintf( deriv, "%s%c", base, DERIVCHAR );

	for( i = 0; strlen( deriv ) < ( NAMELEN * 2 ); i++ )
	{
		if( !pp_sym_get_by_name( g, deriv ) )
			return deriv;

		sprintf( deriv + strlen( deriv ), "%c", DERIVCHAR );
	}

	return (char*)NULL;
}

#define NODE_IS( n, s ) 	( !strcmp( (n)->emit, s ) )

static ppsym* traverse_symbol( ppgram* g, ppsym* lhs, ppast* node )
{
	ppsym*		sym			= (ppsym*)NULL;
	ppast*		child;
	char		name		[ NAMELEN * 2 + 1 ];

	/* fprintf( stderr, "sym >%s<\n", node->emit ); */

	if( NODE_IS( node, "inline") )
	{
		sym = pp_sym_create( g, derive_name( g, lhs->name ),
				PPFLAG_FREENAME | PPFLAG_DEFINED | PPFLAG_GENERATED );

		for( child = node->child; child; child = child->next )
			if( !traverse_production( g, sym, child->child ) )
				return (ppsym*)NULL;
	}
	else if( NODE_IS( node, "Ident") )
	{
		sprintf( name, "%.*s", node->length, node->start );

		if( !( sym = pp_sym_get_by_name( g, name ) ) )
			sym = pp_sym_create( g, name, PPFLAG_FREENAME );
	}
	else
		MISSINGCASE;

	if( sym )
		sym->flags |= PPFLAG_CALLED;

	return sym;
}


static pboolean traverse_production( ppgram* g, ppsym* lhs, ppast* node )
{
	ppsym*		sym;
	ppsym*		csym;
	ppprod*		prod;
	ppprod*		popt;
	ppast*		child;
	char*		str;
	char		name		[ NAMELEN * 2 + 1 ];
	int			i;
	plistel*	e;

	prod = pp_prod_create( g, lhs, (ppsym*)NULL );

	for( ; node; node = node->next )
	{
		/* fprintf( stderr, "prod >%s<\n", node->emit ); */

		if( NODE_IS( node, "symbol" ) )
		{
			if( !( sym = traverse_symbol( g, lhs, node->child ) ) )
				return FALSE;

			pp_prod_append( prod, sym );
		}
		else
		{
			sym = traverse_symbol( g, lhs, node->child->child );
			str = sym->name;

			if( NODE_IS( node, "kle" ) || NODE_IS( node, "pos" ) )
			{
				sprintf( name, "%s%c", str, PPMOD_POSITIVE );

				if( !( csym = pp_sym_get_by_name( g, name ) ) )
				{
					csym = pp_sym_create( g, name,
								PPFLAG_FREENAME | PPFLAG_DEFINED
									| PPFLAG_CALLED | PPFLAG_GENERATED );

					if( g->flags & PPFLAG_PREVENTLREC )
						pp_prod_create( g, csym, sym, csym, (ppsym*)NULL );
					else
						pp_prod_create( g, csym, csym, sym, (ppsym*)NULL );

					pp_prod_create( g, csym, sym, (ppsym*)NULL );
				}

				sym = csym;
			}

			if( NODE_IS( node, "opt" ) || NODE_IS( node, "kle" ) )
			{
				sprintf( name, "%s%c", str, PPMOD_OPTIONAL );

				if( !( csym = pp_sym_get_by_name( g, name ) ) )
				{
					csym = pp_sym_create( g, name,
								PPFLAG_FREENAME | PPFLAG_DEFINED
									| PPFLAG_CALLED | PPFLAG_GENERATED );

					pp_prod_create( g, csym, sym, (ppsym*)NULL );
					pp_prod_create( g, csym, (ppsym*)NULL );
				}

				sym = csym;
			}

			pp_prod_append( prod, sym );
		}
	}

	return TRUE;
}

static pboolean ast_to_gram( ppgram* g, ppast* ast )
{
	ppsym*		sym			= (ppsym*)NULL;
	ppast*		child;
	char		name		[ NAMELEN * 2 + 1 ];

	for( ast; ast; ast = ast->next )
	{
		if( NODE_IS( ast, "nonterm" ) )
		{
			child = ast->child;
			sprintf( name, "%.*s", child->length, child->start );

			/* Create the non-terminal symbol */
			if( !( sym = pp_sym_get_by_name( g, name ) ) )
				sym = pp_sym_create( g, name,
						PPFLAG_FREENAME | PPFLAG_DEFINED );

			for( child = child->next; child; child = child->next )
			{
				if( NODE_IS( child, "production" ) )
				{
					if( !traverse_production( g, sym, child->child ) )
						return FALSE;
				}
				else
					MISSINGCASE;
			}
		}
		else
			MISSINGCASE;
	}

	/* If there is no goal, then the last defined nonterminal
		becomes the goal symbol */
	if( !g->goal )
		g->goal = sym;

	/* Look for unique goal sequence; if this is not the case, wrap it with
		another, generated nonterminal. */
	if( pp_sym_getprod( g->goal, 1 ) )
	{
		sym = pp_sym_create( g, derive_name( g, g->goal->name ),
				PPFLAG_FREENAME | PPFLAG_DEFINED
					| PPFLAG_CALLED | PPFLAG_GENERATED );

		pp_prod_create( g, sym, g->goal, (ppsym*)NULL );
		g->goal = sym;
	}

	return TRUE;
}

/** Compiles a grammar definition into a grammar.

//g// is the grammar that receives the result of the parse.
//bnf// is the BNF definition string that defines the grammar.
*/
pboolean pp_gram_from_bnf( ppgram* g, char* bnf )
{
	plex*		bnflex;
	ppgram*		bnfgram;
	char*		s = bnf;
	char*		e;
	ppast*		ast;

	if( !( g && bnf ) )
	{
		WRONGPARAM;
		return FALSE;
	}

	/* Define grammar for BNF */
	bnfgram = pp_gram_create();
	bnflex = plex_create( 0 );

	pp_bnf_define( bnfgram, bnflex );
	/* pp_gram_dump( stdout, bnfgram ); */ /* DEBUG */

	if( !pp_lr_parse( &ast, bnfgram, bnflex, s, &e ) )
	{
		pp_gram_free( bnfgram );
		return FALSE;
	}

	/* pp_ast_dump_short( stdout, ast ); */

	if( !ast_to_gram( g, ast ) )
		return FALSE;

	pp_gram_free( bnfgram );
	pp_ast_free( ast );

	return TRUE;
}


/** Dumps the grammar //g// to //stream//. */
void pp_gram_dump( FILE* stream, ppgram* g )
{
	plistel*	e;
	plistel*	f;
	ppprod*		p;
	ppsym*		s;
	size_t		maxlhslen	= 0;
	size_t		maxemitlen	= 0;
	size_t		maxsymlen	= 0;

	plist_for( g->symbols, e )
	{
		s = (ppsym*)plist_access( e );

		if( pstrlen( s->emit ) > maxemitlen )
			maxemitlen = pstrlen( s->emit );

		if( PPSYM_IS_NONTERMINAL( s ) && pstrlen( s->name ) > maxlhslen )
			maxlhslen = pstrlen( s->name );

		if( pstrlen( s->name ) > maxsymlen )
			maxsymlen = pstrlen( s->name );
	}

	plist_for( g->prods, e )
	{
		p = (ppprod*)plist_access( e );
		fprintf( stream,
			"%s%s%s%s%s%s%-*s %-*s : ",
			g->goal == p->lhs ? "$" : " ",
			p->flags & PPFLAG_LEFTREC ? "L" : " ",
			p->flags & PPFLAG_NULLABLE ? "N" : " ",
			p->lhs->flags & PPFLAG_LEXEM ? "X" : " ",
			p->lhs->flags & PPFLAG_WHITESPACE ? "W" : " ",
			p->emit ? "@" : " ",
			maxemitlen, p->emit ? p->emit : "",
			maxlhslen, p->lhs->name );

		plist_for( p->rhs, f )
		{
			s = (ppsym*)plist_access( f );

			if( f != plist_first( p->rhs ) )
				fprintf( stream, " " );

			fprintf( stream, "%s", pp_sym_to_str( s ) );
		}

		fprintf( stream, "\n" );
	}

	fprintf( stream, "\n" );

	plist_for( g->symbols, e )
	{
		s = (ppsym*)plist_access( e );

		fprintf( stream, "%03d  %-*s  %-*s",
			s->idx, maxemitlen, s->emit ? s->emit : "",
				maxsymlen, s->name );

		if( PPSYM_IS_NONTERMINAL( s ) )
		{
			fprintf( stream, " {" );

			plist_for( s->first, f )
			{
				s = (ppsym*)plist_access( f );
				fprintf( stream, " " );
				fprintf( stream, "%s", pp_sym_to_str( s ) );
			}

			fprintf( stream, " }" );
		}

		fprintf( stream, "\n" );
	}
}

/** Frees grammar //g// and all its related memory. */
ppgram* pp_gram_free( ppgram* g )
{
	plistel*	e;
	ppsym*		s;
	ppprod*		p;

	if( !g )
		return (ppgram*)NULL;

	/* Erase symbols */
	while( plist_count( g->symbols ) )
		pp_sym_free( (ppsym*)plist_access( plist_first( g->symbols ) ) );

	/* Erase productions */
	while( plist_count( g->prods ) )
		pp_prod_free( (ppprod*)plist_access( plist_first( g->prods ) ) );

	plist_free( g->symbols );
	plist_free( g->prods );

	pfree( g );

	return (ppgram*)NULL;
}
