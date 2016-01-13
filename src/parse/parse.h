/* -HEADER----------------------------------------------------------------------
Phorward Foundation Toolkit
Copyright (C) 2006-2016 by Phorward Software Technologies, Jan Max Meyer
http://www.phorward-software.com ++ contact<at>phorward<dash>software<dot>com
All rights reserved. See LICENSE for more information.

File:	parse.h
Usage:	Phorward Parsing Library
		THIS SOURCE IS UNDER DEVELOPMENT AND EXPERIMENTAL.
----------------------------------------------------------------------------- */

typedef struct _ppsym		ppsym;
typedef struct _ppprod		ppprod;
typedef struct _ppgram		ppgram;
typedef struct _ppast		ppast;

/* Flags for grammars and their objects */
#define PPFLAG_CALLED		1
#define PPFLAG_DEFINED		2
#define PPFLAG_NULLABLE		4
#define PPFLAG_LEFTREC		8
#define PPFLAG_LEXEM		16
#define PPFLAG_WHITESPACE	32
#define PPFLAG_PREVENTLREC	64
#define PPFLAG_NAMELESS		128

#define PPMOD_OPTIONAL		'?'
#define PPMOD_POSITIVE		'+'
#define PPMOD_KLEENE		'*'

/* Production */
struct _ppprod
{
	/* Primaries */
	int						id;
	ppsym*					lhs;
	plist*					rhs;
	int						flags;

	/* AST construction */
	int						emit;
	char*					semit;

	/* Debug */
	char*					strval;
};

/* Symbol types */
typedef enum
{
	PPSYMTYPE_NONTERM,
	PPSYMTYPE_CCL,
	PPSYMTYPE_STRING,
	PPSYMTYPE_REGEX,
	PPSYMTYPE_FUNCTION,
	PPSYMTYPE_SPECIAL
} ppsymtype;

/* Symbol function */
typedef pboolean (*ppsymfunc)( char* start, char** end );

/* Symbol */
struct _ppsym
{
	/* Primaries */
	int						id;
	ppsymtype				type;
	char*					name;
	int						flags;

	/* Nonterminal specific */
	plist*					first;
	plist*					prods;

	/* Terminal specific */
	pccl*					ccl;		/* Character class */
	char*					str;		/* String */
	pregex*					re;			/* Regular expression */
	ppsymfunc				sf;			/* Symbol function */

	/* AST construction */
	int						emit;
	char*					semit;

	/* Debug */
	char*					strval;
};

/* Grammar */
struct _ppgram
{
	plist*					symbols;
	plist*					prods;

	plist*					ws;
	ppsym*					goal;
	ppsym*					eof;

	ppsymfunc 				(*getsymfunc)( char* name );

	int						flags;
};

/* AST */
struct _ppast
{
	int						emit;
	char*					semit;

	ppsym*					sym;
	ppprod*					prod;

	char*					start;
	char*					end;
	int						row;
	int						col;

	ppast*					child;
	ppast*					next;
};

/* Match (an AST entry) */
typedef struct
{
	#define PPMATCH_BEGIN	1
	#define PPMATCH_END		2
	int						type;

	int						emit;
	char*					semit;
	ppsym*					sym;
	ppprod*					prod;

	char*					start;
	char*					end;
	int						row;
	int						col;
} ppmatch;

/* Parser maintainance/runtime object */
typedef struct
{
	int						type;
	ppgram*					gram;
} pparse;
