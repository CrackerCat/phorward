/* -MODULE----------------------------------------------------------------------
Phorward Foundation Toolkit
Copyright (C) 2006-2015 by Phorward Software Technologies, Jan Max Meyer
http://www.phorward-software.com ++ contact<at>phorward<dash>software<dot>com
All rights reserved. See LICENSE for more information.

File:	mygram.c
Usage:	Self-contained parser for ppgram.
----------------------------------------------------------------------------- */

/*
	This file was automatically generated by pinclude.
	DO NOT CHANGE THIS FILE MANUALLY. IT WILL GO AWAY!
*/


#include "phorward.h"

void pp_gram4myself( ppgram* g )
{

	ppsym*	sym[ 62 ];

	

	sym[ 1 ] = pp_sym_create( g, PPSYMTYPE_STRING, "kw_emit", "emit" );

	sym[ 2 ] = pp_sym_create( g, PPSYMTYPE_STRING, "kw_noemit", "noemit" );

	sym[ 3 ] = pp_sym_create( g, PPSYMTYPE_STRING, "kw_goal", "goal" );

	sym[ 4 ] = pp_sym_create( g, PPSYMTYPE_STRING, "kw_ws", "whitespace" );

	sym[ 5 ] = pp_sym_create( g, PPSYMTYPE_STRING, "kw_emitall", "emitall" );

	sym[ 6 ] = pp_sym_create( g, PPSYMTYPE_STRING, "kw_emitnone", "emitnone" );

	sym[ 7 ] = pp_sym_create( g, PPSYMTYPE_STRING, "kw_lrec", "lrec" );

	sym[ 8 ] = pp_sym_create( g, PPSYMTYPE_STRING, "kw_rrec", "rrec" );

	sym[ 9 ] = pp_sym_create( g, PPSYMTYPE_REGEX, "ws", "[\\t\\n\\r ]+" );
	sym[ 9 ]->flags |= PPFLAG_WHITESPACE;

	sym[ 10 ] = pp_sym_create( g, PPSYMTYPE_REGEX, "ccl", "'.*'" );
	sym[ 10 ]->emit = 1;

	sym[ 11 ] = pp_sym_create( g, PPSYMTYPE_REGEX, "string", "\".*\"" );
	sym[ 11 ]->emit = 2;

	sym[ 12 ] = pp_sym_create( g, PPSYMTYPE_REGEX, "regex", "/(\\.|[^/])*/" );
	sym[ 12 ]->emit = 3;

	sym[ 13 ] = pp_sym_create( g, PPSYMTYPE_REGEX, "ident", "[A-Z_a-z][0-9A-Z_a-z]*" );
	sym[ 13 ]->emit = 10;

	sym[ 14 ] = pp_sym_create( g, PPSYMTYPE_REGEX, "int", "[0-9]+" );
	sym[ 14 ]->emit = 11;

	sym[ 15 ] = pp_sym_create( g, PPSYMTYPE_NONTERM, "symbol", (char*)NULL );
	sym[ 15 ]->emit = 20;

	sym[ 16 ] = pp_sym_create( g, PPSYMTYPE_NONTERM, "inline", (char*)NULL );
	sym[ 16 ]->emit = 32;

	sym[ 17 ] = pp_sym_create( g, PPSYMTYPE_NONTERM, "mod_kleene", (char*)NULL );
	sym[ 17 ]->emit = 25;

	sym[ 18 ] = pp_sym_create( g, PPSYMTYPE_CCL, "*", "*" );

	sym[ 19 ] = pp_sym_create( g, PPSYMTYPE_NONTERM, "mod_positive", (char*)NULL );
	sym[ 19 ]->emit = 26;

	sym[ 20 ] = pp_sym_create( g, PPSYMTYPE_CCL, "+", "+" );

	sym[ 21 ] = pp_sym_create( g, PPSYMTYPE_NONTERM, "mod_optional", (char*)NULL );
	sym[ 21 ]->emit = 27;

	sym[ 22 ] = pp_sym_create( g, PPSYMTYPE_CCL, "?", "?" );

	sym[ 23 ] = pp_sym_create( g, PPSYMTYPE_NONTERM, "modifier", (char*)NULL );

	sym[ 24 ] = pp_sym_create( g, PPSYMTYPE_NONTERM, "sequence", (char*)NULL );

	sym[ 25 ] = pp_sym_create( g, PPSYMTYPE_NONTERM, "alternative", (char*)NULL );
	sym[ 25 ]->emit = 30;

	sym[ 26 ] = pp_sym_create( g, PPSYMTYPE_NONTERM, "alternation", (char*)NULL );

	sym[ 27 ] = pp_sym_create( g, PPSYMTYPE_CCL, "|", "|" );

	sym[ 28 ] = pp_sym_create( g, PPSYMTYPE_NONTERM, "emit", (char*)NULL );
	sym[ 28 ]->emit = 42;

	sym[ 29 ] = pp_sym_create( g, PPSYMTYPE_NONTERM, "emit'", (char*)NULL );

	sym[ 30 ] = pp_sym_create( g, PPSYMTYPE_NONTERM, "flag", (char*)NULL );
	sym[ 30 ]->emit = 40;

	sym[ 31 ] = pp_sym_create( g, PPSYMTYPE_NONTERM, "emitflag", (char*)NULL );

	sym[ 32 ] = pp_sym_create( g, PPSYMTYPE_NONTERM, "flags", (char*)NULL );

	sym[ 33 ] = pp_sym_create( g, PPSYMTYPE_CCL, "%", "%" );

	sym[ 34 ] = pp_sym_create( g, PPSYMTYPE_NONTERM, "flags'", (char*)NULL );

	sym[ 35 ] = pp_sym_create( g, PPSYMTYPE_CCL, "%", "%" );

	sym[ 36 ] = pp_sym_create( g, PPSYMTYPE_NONTERM, "flags''", (char*)NULL );

	sym[ 37 ] = pp_sym_create( g, PPSYMTYPE_NONTERM, "nontermdef", (char*)NULL );
	sym[ 37 ]->emit = 31;

	sym[ 38 ] = pp_sym_create( g, PPSYMTYPE_CCL, ":", ":" );

	sym[ 39 ] = pp_sym_create( g, PPSYMTYPE_NONTERM, "nontermdef'", (char*)NULL );

	sym[ 40 ] = pp_sym_create( g, PPSYMTYPE_CCL, ";", ";" );

	sym[ 41 ] = pp_sym_create( g, PPSYMTYPE_CCL, "(", "(" );

	sym[ 42 ] = pp_sym_create( g, PPSYMTYPE_CCL, ")", ")" );

	sym[ 43 ] = pp_sym_create( g, PPSYMTYPE_NONTERM, "termdef", (char*)NULL );
	sym[ 43 ]->emit = 35;

	sym[ 44 ] = pp_sym_create( g, PPSYMTYPE_CCL, "=", "=" );

	sym[ 45 ] = pp_sym_create( g, PPSYMTYPE_NONTERM, "termdef'", (char*)NULL );

	sym[ 46 ] = pp_sym_create( g, PPSYMTYPE_CCL, ";", ";" );

	sym[ 47 ] = pp_sym_create( g, PPSYMTYPE_CCL, "=", "=" );

	sym[ 48 ] = pp_sym_create( g, PPSYMTYPE_NONTERM, "termdef''", (char*)NULL );

	sym[ 49 ] = pp_sym_create( g, PPSYMTYPE_CCL, ";", ";" );

	sym[ 50 ] = pp_sym_create( g, PPSYMTYPE_CCL, "=", "=" );

	sym[ 51 ] = pp_sym_create( g, PPSYMTYPE_NONTERM, "termdef'''", (char*)NULL );

	sym[ 52 ] = pp_sym_create( g, PPSYMTYPE_CCL, ";", ";" );

	sym[ 53 ] = pp_sym_create( g, PPSYMTYPE_NONTERM, "gflag", (char*)NULL );
	sym[ 53 ]->emit = 41;

	sym[ 54 ] = pp_sym_create( g, PPSYMTYPE_NONTERM, "gflags", (char*)NULL );

	sym[ 55 ] = pp_sym_create( g, PPSYMTYPE_CCL, "%", "%" );

	sym[ 56 ] = pp_sym_create( g, PPSYMTYPE_NONTERM, "gflags'", (char*)NULL );

	sym[ 57 ] = pp_sym_create( g, PPSYMTYPE_CCL, "%", "%" );

	sym[ 58 ] = pp_sym_create( g, PPSYMTYPE_NONTERM, "gflags''", (char*)NULL );

	sym[ 59 ] = pp_sym_create( g, PPSYMTYPE_NONTERM, "definition", (char*)NULL );

	sym[ 60 ] = pp_sym_create( g, PPSYMTYPE_NONTERM, "grammar", (char*)NULL );
	g->goal = sym[ 60 ];

	sym[ 61 ] = pp_sym_create( g, PPSYMTYPE_NONTERM, "grammar'", (char*)NULL );


	

	pp_prod_create( g, sym[ 15 ] ,
		sym[ 13 ], 
		(ppsym*)NULL );

	pp_prod_create( g, sym[ 15 ] ,
		sym[ 10 ], 
		(ppsym*)NULL );

	pp_prod_create( g, sym[ 15 ] ,
		sym[ 11 ], 
		(ppsym*)NULL );

	pp_prod_create( g, sym[ 15 ] ,
		sym[ 12 ], 
		(ppsym*)NULL );

	pp_prod_create( g, sym[ 15 ] ,
		sym[ 16 ], 
		(ppsym*)NULL );

	pp_prod_create( g, sym[ 17 ] ,
		sym[ 15 ], 
		sym[ 18 ], 
		(ppsym*)NULL );

	pp_prod_create( g, sym[ 19 ] ,
		sym[ 15 ], 
		sym[ 20 ], 
		(ppsym*)NULL );

	pp_prod_create( g, sym[ 21 ] ,
		sym[ 15 ], 
		sym[ 22 ], 
		(ppsym*)NULL );

	pp_prod_create( g, sym[ 23 ] ,
		sym[ 17 ], 
		(ppsym*)NULL );

	pp_prod_create( g, sym[ 23 ] ,
		sym[ 19 ], 
		(ppsym*)NULL );

	pp_prod_create( g, sym[ 23 ] ,
		sym[ 21 ], 
		(ppsym*)NULL );

	pp_prod_create( g, sym[ 23 ] ,
		sym[ 15 ], 
		(ppsym*)NULL );

	pp_prod_create( g, sym[ 24 ] ,
		sym[ 24 ], 
		sym[ 23 ], 
		(ppsym*)NULL );

	pp_prod_create( g, sym[ 24 ] ,
		sym[ 23 ], 
		(ppsym*)NULL );

	pp_prod_create( g, sym[ 25 ] ,
		sym[ 24 ], 
		(ppsym*)NULL );

	pp_prod_create( g, sym[ 25 ] , (ppsym*)NULL );

	pp_prod_create( g, sym[ 26 ] ,
		sym[ 26 ], 
		sym[ 27 ], 
		sym[ 25 ], 
		(ppsym*)NULL );

	pp_prod_create( g, sym[ 26 ] ,
		sym[ 25 ], 
		(ppsym*)NULL );

	pp_prod_create( g, sym[ 28 ] ,
		sym[ 1 ], 
		sym[ 29 ], 
		(ppsym*)NULL );

	pp_prod_create( g, sym[ 29 ] ,
		sym[ 14 ], 
		(ppsym*)NULL );

	pp_prod_create( g, sym[ 29 ] , (ppsym*)NULL );

	pp_prod_create( g, sym[ 30 ] ,
		sym[ 2 ], 
		(ppsym*)NULL );

	pp_prod_create( g, sym[ 30 ] ,
		sym[ 3 ], 
		(ppsym*)NULL );

	pp_prod_create( g, sym[ 30 ] ,
		sym[ 4 ], 
		(ppsym*)NULL );

	pp_prod_create( g, sym[ 31 ] ,
		sym[ 28 ], 
		(ppsym*)NULL );

	pp_prod_create( g, sym[ 31 ] ,
		sym[ 30 ], 
		(ppsym*)NULL );

	pp_prod_create( g, sym[ 32 ] ,
		sym[ 32 ], 
		sym[ 33 ], 
		sym[ 34 ], 
		(ppsym*)NULL );

	pp_prod_create( g, sym[ 34 ] ,
		sym[ 34 ], 
		sym[ 31 ], 
		(ppsym*)NULL );

	pp_prod_create( g, sym[ 34 ] ,
		sym[ 31 ], 
		(ppsym*)NULL );

	pp_prod_create( g, sym[ 32 ] ,
		sym[ 35 ], 
		sym[ 36 ], 
		(ppsym*)NULL );

	pp_prod_create( g, sym[ 36 ] ,
		sym[ 36 ], 
		sym[ 31 ], 
		(ppsym*)NULL );

	pp_prod_create( g, sym[ 36 ] ,
		sym[ 31 ], 
		(ppsym*)NULL );

	pp_prod_create( g, sym[ 37 ] ,
		sym[ 13 ], 
		sym[ 38 ], 
		sym[ 26 ], 
		sym[ 39 ], 
		sym[ 40 ], 
		(ppsym*)NULL );

	pp_prod_create( g, sym[ 39 ] ,
		sym[ 32 ], 
		(ppsym*)NULL );

	pp_prod_create( g, sym[ 39 ] , (ppsym*)NULL );

	pp_prod_create( g, sym[ 16 ] ,
		sym[ 41 ], 
		sym[ 26 ], 
		sym[ 42 ], 
		(ppsym*)NULL );

	pp_prod_create( g, sym[ 43 ] ,
		sym[ 13 ], 
		sym[ 44 ], 
		sym[ 10 ], 
		sym[ 45 ], 
		sym[ 46 ], 
		(ppsym*)NULL );

	pp_prod_create( g, sym[ 45 ] ,
		sym[ 32 ], 
		(ppsym*)NULL );

	pp_prod_create( g, sym[ 45 ] , (ppsym*)NULL );

	pp_prod_create( g, sym[ 43 ] ,
		sym[ 13 ], 
		sym[ 47 ], 
		sym[ 11 ], 
		sym[ 48 ], 
		sym[ 49 ], 
		(ppsym*)NULL );

	pp_prod_create( g, sym[ 48 ] ,
		sym[ 32 ], 
		(ppsym*)NULL );

	pp_prod_create( g, sym[ 48 ] , (ppsym*)NULL );

	pp_prod_create( g, sym[ 43 ] ,
		sym[ 13 ], 
		sym[ 50 ], 
		sym[ 12 ], 
		sym[ 51 ], 
		sym[ 52 ], 
		(ppsym*)NULL );

	pp_prod_create( g, sym[ 51 ] ,
		sym[ 32 ], 
		(ppsym*)NULL );

	pp_prod_create( g, sym[ 51 ] , (ppsym*)NULL );

	pp_prod_create( g, sym[ 53 ] ,
		sym[ 5 ], 
		(ppsym*)NULL );

	pp_prod_create( g, sym[ 53 ] ,
		sym[ 6 ], 
		(ppsym*)NULL );

	pp_prod_create( g, sym[ 53 ] ,
		sym[ 7 ], 
		(ppsym*)NULL );

	pp_prod_create( g, sym[ 53 ] ,
		sym[ 8 ], 
		(ppsym*)NULL );

	pp_prod_create( g, sym[ 54 ] ,
		sym[ 54 ], 
		sym[ 55 ], 
		sym[ 56 ], 
		(ppsym*)NULL );

	pp_prod_create( g, sym[ 56 ] ,
		sym[ 56 ], 
		sym[ 53 ], 
		(ppsym*)NULL );

	pp_prod_create( g, sym[ 56 ] ,
		sym[ 53 ], 
		(ppsym*)NULL );

	pp_prod_create( g, sym[ 54 ] ,
		sym[ 57 ], 
		sym[ 58 ], 
		(ppsym*)NULL );

	pp_prod_create( g, sym[ 58 ] ,
		sym[ 58 ], 
		sym[ 53 ], 
		(ppsym*)NULL );

	pp_prod_create( g, sym[ 58 ] ,
		sym[ 53 ], 
		(ppsym*)NULL );

	pp_prod_create( g, sym[ 59 ] ,
		sym[ 37 ], 
		(ppsym*)NULL );

	pp_prod_create( g, sym[ 59 ] ,
		sym[ 43 ], 
		(ppsym*)NULL );

	pp_prod_create( g, sym[ 59 ] ,
		sym[ 54 ], 
		(ppsym*)NULL );

	pp_prod_create( g, sym[ 60 ] ,
		sym[ 61 ], 
		(ppsym*)NULL );

	pp_prod_create( g, sym[ 61 ] ,
		sym[ 61 ], 
		sym[ 59 ], 
		(ppsym*)NULL );

	pp_prod_create( g, sym[ 61 ] ,
		sym[ 59 ], 
		(ppsym*)NULL );



}
