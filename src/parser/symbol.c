/* -MODULE----------------------------------------------------------------------
Phorward Foundation Toolkit
Copyright (C) 2006-2013 by Phorward Software Technologies, Jan Max Meyer
http://www.phorward-software.com ++ contact<at>phorward<dash>software<dot>com
All rights reserved. See LICENSE for more information.

File:	grammar.c
Usage:
----------------------------------------------------------------------------- */

#include "local.h"

/* Constructor */

pgsymbol* pg_symbol_create( pggrammar* grammar, pgsymtype type, uchar* name )
{
	pgsymbol	sym;
	punit*	e;
	uchar*		symname;

	PROC( "pg_symbol_create" );
	PARMS( "type", "%d", type );
	PARMS( "name", "%s", name );

	if( !( grammar && name && *name ) )
	{
		WRONGPARAM;
		return (pgsymbol*)NULL;
	}

	if( plist_get_by_key( grammar->symbols, name ) )
	{
		TODO;
		fprintf( stderr, "Symbol '%s' already exists in this grammar\n", name );
		return (pgsymbol*)NULL;
	}

	memset( &sym, 0, sizeof( pgsymbol ) );
	sym.type = type;
	sym.grammar = grammar;
	sym.id = plist_count( grammar->symbols );
	sym.name = pstrdup( name );

	e = plist_insert( grammar->symbols, (punit*)NULL, sym.name, (pbyte*)&sym );

	return (pgsymbol*)plist_access( e );
}

/* Destructor */

pgsymbol* pg_symbol_free( pgsymbol* symbol )
{
	punit*		se;
	punit*		nse;
	pgsymbol*	move;

	if( !( symbol ) )
		return (pgsymbol*)NULL;

	/* Find unit in symbol table */
	if( !( nse = se = plist_get_by_ptr( symbol->grammar->symbols, symbol ) ) )
		return symbol;

	/* Move up all symbols from here */
	while( ( nse = plist_next( nse ) ) )
	{
		move = (pgsymbol*)plist_access( nse );
		move->id--;
	}

	/* Free members */
	pfree( symbol->name );

	/* Remove from symbol list */
	plist_remove( symbol->grammar->symbols, se );

	return (pgsymbol*)NULL;
}

/* Check */

/** Check if //symbol// is of type **PGSYMTYPE_TERMINAL**. */
BOOLEAN pg_symbol_is_terminal( pgsymbol* symbol )
{
	if( symbol && pg_symbol_get_type( symbol ) == PGSYMTYPE_TERMINAL  )
		return TRUE;

	return FALSE;
}

/** Check if //symbol// is of type **PGSYMTYPE_NONTERMINAL**. */
BOOLEAN pg_symbol_is_nonterminal( pgsymbol* symbol )
{
	if( symbol && pg_symbol_get_type( symbol ) == PGSYMTYPE_NONTERMINAL  )
		return TRUE;

	return FALSE;
}

/* Attribute: type */

/* GET ONLY! */
pgsymtype pg_symbol_get_type( pgsymbol* symbol )
{
	if( !( symbol ) )
	{
		WRONGPARAM;
		return PGSYMTYPE_UNDEFINED;
	}

	return symbol->type;
}

/* Attribute: grammar */

/* GET ONLY! */
pggrammar* pg_symbol_get_grammar( pgsymbol* symbol )
{
	if( !( symbol ) )
	{
		WRONGPARAM;
		return (pggrammar*)NULL;
	}

	return symbol->grammar;
}
