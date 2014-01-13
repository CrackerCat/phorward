/*
	This file was automatically generated by pinclude.
	Source files: phorward.tpl.h
*/



#ifndef _PHORWARD_H
#define _PHORWARD_H


#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#include <stdarg.h>

#ifndef va_copy
#define va_copy( a, b )	(a) = (b)
#endif

#include <limits.h>
#include <time.h>
#include <fcntl.h>

#include <sys/stat.h>
#include <sys/types.h>

#ifdef UNICODE
#include <locale.h>
#include <wchar.h>
#include <wctype.h>
#endif

#ifdef _WIN32
#include <process.h>
#else
#include <unistd.h>
#endif




#ifdef UNICODE
typedef wchar_t					wchar;
#else
typedef int						wchar;
#endif


typedef unsigned char			pbyte;		
typedef wchar					pchar;		
typedef	int						pint;		
typedef	float					pfloat;		
typedef double					pdouble;	
typedef long					plong;		
typedef size_t					pulong;		
typedef size_t					psize;		



typedef char 					pboolean;	
#ifndef BOOLEAN
#define BOOLEAN					pboolean
#endif

#ifndef boolean
#define boolean 				pboolean
#endif

#ifndef TRUE
#define TRUE					1
#endif

#ifndef FALSE
#define FALSE					0
#endif

#define BOOLEAN_STR( b ) 		( ( b ) ? "TRUE" : "FALSE" )
#define TRUEBOOLEAN( b ) 		( ( b ) ? TRUE : FALSE )


#define ERR_OK					0		
#define ERR_FAILURE				-1		
#define ERR_PARMS				-2		
#define ERR_MEM					-3		
#define ERR_SYSTEM				-4		
#define ERR_UNIMPL				-5		
#define ERR_OTHER				-6		


#define OUTOFMEM				fprintf( stderr, \
									"%s, %d: Ran out of memory\n", \
										__FILE__, __LINE__ ), exit( 1 )

#define WRONGPARAM				fprintf( stderr, \
									"%s, %d: Function called with wrong or " \
									"incomplete parameters, fix your call!\n", \
										__FILE__, __LINE__ )

#define MISSINGCASE				fprintf( stderr, \
									"%s, %d: Missing case enganged, " \
									"please check for correctness.", \
									__FILE__, __LINE__ )

#define TODO					fprintf( stderr, \
									"%s, %d: TODO alert! The program ran into "\
									"a module that is not finished yet!\n", \
											__FILE__, __LINE__ )


#ifndef _WIN32
#define PDIRSEP					':'
#define PPATHSEP				'/'
#else
#define PDIRSEP					';'
#define PPATHSEP				'\\'
#endif






#ifndef _DBG_H
#define _DBG_H


#ifdef DEBUG
	#define PROC( name ) \
		static char*	_dbg_proc_name	= name; \
		_dbg_trace( __FILE__, __LINE__, "ENTRY", "%s", _dbg_proc_name )
#else
	#define PROC( name )
#endif


#ifdef DEBUG
	#define RETURN( val ) \
		do \
		{ \
			_dbg_trace( __FILE__, __LINE__, \
				"RETURN", "%s", _dbg_proc_name ); \
			return val; \
		} \
		while( 0 )
#else
	#define RETURN( val ) return val
#endif


#ifdef DEBUG
	#define VOIDRET \
		do \
		{ \
			_dbg_trace( __FILE__, __LINE__, \
				"RETURN", "%s", _dbg_proc_name ); \
			return; \
		} \
		while( 0 )
#else
	#define VOIDRET return
#endif


#ifdef DEBUG
	#define MSG( text ) \
		_dbg_trace( __FILE__, __LINE__, "MSG", "%s", text )
#else
	#define MSG( text )
#endif


#ifdef DEBUG
	#define VARS( name, format, val ) \
		_dbg_trace( __FILE__, __LINE__, "VARS", "%s = >" format "<", name, val )
#else
	#define VARS( name, format, val )
#endif


#ifdef DEBUG
	#define PARMS( name, format, val ) \
		_dbg_trace( __FILE__, __LINE__, "PARMS", \
			"%s = >" format "<", name, val )
#else
	#define PARMS( name, format, val )
#endif

#endif



#ifndef LLIST_H
#define LLIST_H


typedef struct llist
{
	void*			pptr;
	struct llist*	next;
} LIST;


#define list_access( ll )		( (ll) ? (ll)->pptr : (void*)NULL )
#define list_next( ll )			( (ll) ? (ll)->next : (LIST*)NULL )
#define list_replace( ll, ptr )	( (ll) ? (ll)->pptr = (ptr) : 0 )

#define LISTFOR( ll, cc )		for( (cc) = (ll); (cc); (cc) = list_next(cc) )

#endif




#ifndef PLIST_H
#define PLIST_H


#define PLIST_MOD_NONE		0	
#define PLIST_MOD_PTR		1	
#define PLIST_MOD_RECYCLE	2	
#define PLIST_MOD_AUTOSORT	4	
#define PLIST_MOD_EXTKEYS	8	
#define PLIST_MOD_UNIQUE	16	
#define PLIST_MOD_WCHAR		32	



typedef struct Plistel		plistel;
typedef struct Plist		plist;


struct Plistel
{
	char*					key;
	plist*					list;

	plistel*				prev;
	plistel*				next;

	plistel*				hashnext;
	plistel*				hashprev;
};


struct Plist
{
	int						flags;
	int						size;
	int						count;
	int						hashsize;

	int						(*comparefn)( plist*, plistel*, plistel* );
	int						(*sortfn)( plist*, plistel*, plistel* );

	plistel*				unused;

	plistel*				first;
	plistel*				last;
	plistel**				hash;
};





#define plist_for( l, e )	\
	for( (e) = plist_first( l ); (e); (e) = plist_next( e ) )

#endif 



#ifndef STACK_H
#define STACK_H

typedef struct
{
	void*	stack;
	size_t	size;
	size_t	top;
	size_t	count;
	size_t	step;
} pstack;

#endif



#ifndef PUNION_H
#define PUNION_H


#define PUNION_NULL			0	
#define PUNION_BYTE			1
#define PUNION_CHAR			2
#define PUNION_INT			3
#define PUNION_LONG			4
#define PUNION_ULONG		5
#define PUNION_FLOAT		6
#define PUNION_DOUBLE		7
#define PUNION_STRING		8
#define PUNION_WSTRING		9

#define PUNION_IS_CONSTANT	16	
#define PUNION_IS_CONVERT	32	


typedef struct 
{
	pbyte		type;

	union
	{
		pbyte	b;
		

		char	c;
		

		pint	i;
		

		plong	l;
		

		pulong	ul;
		

		pfloat	f;
		

		pdouble	d;
		

		char*	s;
		
		

		pchar*	ws;
		
		
	} val;
} punion;


#define punion_set_string_d( var, val ) \
			punion_set_string( var, pstrdup( val ) )
#define punion_set_wstring_d( var, val ) \
			punion_set_wstring( var, pwcsdup( val ) )

#define punion_set_constant( var ) \
			(var)->type |= PUNION_IS_CONSTANT
#define punion_unset_constant( var ) \
			(var)->type &= ~PUNION_IS_CONSTANT
#define punion_set_convertible( var ) \
			(var)->type |= PUNION_IS_CONVERT
#define punion_unset_convertible( var ) \
			(var)->type &= ~PUNION_IS_CONVERT

#define punion_type( var ) \
			( ( var )->type & 0x0F )
#define punion_is_constant( var ) \
			( ( var )->type & PUNION_IS_CONSTANT )
#define punion_is_convertible( var ) \
			( ( var )->type & PUNION_IS_CONVERT )

#endif






#ifndef _XML_H
#define _XML_H

#define XML_BUFSIZE 1024	
#define XML_NAMEM	0x80	
#define XML_TXTM	0x40	
#define XML_DUP		0x20	

typedef struct xml*		XML_T;
struct xml
{
	char*		name;		
	char **	 attr;		
	char*		txt;		
	size_t		off;		
	int			line;		
	XML_T		next;		
	XML_T		sibling;	
	XML_T		ordered;	
	XML_T		child;		
	XML_T		parent;		
	short		flags;		
};

#define xml_next( xml )		\
	( ( xml ) ? xml->next : NULL )

#define xml_next_inorder( xml ) \
	((xml) ? xml->ordered : NULL)

#define xml_name( xml )	\
	( ( xml ) ? xml->name : NULL )

#define xml_txt( xml ) \
	( ( xml ) ? xml->txt : "" )
	
#define xml_line(xml) \
	( ( xml ) ? (xml)->line : 0 )

#define xml_new_d( name ) \
	xml_set_flag( xml_new( pstrdup(name) ),XML_NAMEM )

#define xml_add_child_d( xml, name, off ) \
	xml_set_flag \
	( \
		xml_add_child( xml, pstrdup(name), off ), \
		XML_NAMEM \
	)

#define xml_set_txt_d( xml, txt ) \
	xml_set_flag \
	( \
		xml_set_txt( xml, pstrdup(txt) ), \
		XML_TXTM \
	)

#define xml_set_attr_d( xml, name, value ) \
	xml_set_attr \
	( \
		xml_set_flag( xml, XML_DUP ), \
		pstrdup( name ), \
		pstrdup( value ) \
	)
	
#define xml_add_child_f( xml, name, off ) \
	xml_set_flag \
	( \
		xml_add_child( xml, name, off ), \
		XML_NAMEM \
	)
	
#define xml_set_txt_f( xml, txt ) \
	xml_set_flag \
	( \
		xml_set_txt( xml, txt ), \
		XML_TXTM \
	)

#define xml_set_attr_f( xml, name, value ) \
	xml_set_attr \
	( \
		xml_set_flag( xml, XML_DUP ), \
		pstrdup( name ), \
		(value) \
	)

#define xml_move( xml, dest, off )	\
	xml_insert( xml_cut( xml ),dest,off )

#define xml_remove( xml ) \
	xml_free( xml_cut( xml ) )

#endif 





#define PREGEX_ACCEPT_NONE		-1

#define PREGEX_ALLOC_STEP		16


#define PREGEX_STAT_NONE		0
#define PREGEX_STAT_NFA			1
#define PREGEX_STAT_DFA			2


#define PREGEX_MOD_NONE			0		
#define PREGEX_MOD_WCHAR		1		
#define PREGEX_MOD_INSENSITIVE	2		
#define PREGEX_MOD_GLOBAL		4		
#define PREGEX_MOD_STATIC		8		
#define PREGEX_MOD_NO_REF		16		
#define PREGEX_MOD_NO_ERRORS	32		
#define PREGEX_MOD_NO_ANCHORS	64		
#define PREGEX_MOD_GREEDY		128		
#define PREGEX_MOD_NONGREEDY	256		
#define PREGEX_MOD_DEBUG		1024 	


#define PREGEX_ANCHOR_NONE		0	
#define PREGEX_ANCHOR_BOL		1	
#define PREGEX_ANCHOR_EOL		2	
#define PREGEX_ANCHOR_BOW		4	
#define PREGEX_ANCHOR_EOW		8	


enum _regex_ptntype
{
	PREGEX_PTN_NULL,
	PREGEX_PTN_CHAR,
	PREGEX_PTN_SUB,
	PREGEX_PTN_ALT,
	PREGEX_PTN_KLE,
	PREGEX_PTN_POS,
	PREGEX_PTN_OPT
};


typedef struct	_regex_cr		pregex_cr;
typedef struct	_regex_ccl		pregex_ccl;

typedef struct	_regex_accept	pregex_accept;

typedef struct	_regex_nfa_st	pregex_nfa_st;
typedef struct	_regex_nfa		pregex_nfa;

typedef struct	_regex_dfa_tr	pregex_dfa_tr;
typedef struct	_regex_dfa_st	pregex_dfa_st;
typedef struct	_regex_dfa		pregex_dfa;

typedef enum 	_regex_ptntype	pregex_ptntype;
typedef struct	_regex_ptn		pregex_ptn;

typedef struct	_regex			pregex;
typedef	struct	_regex_range	pregex_range;

typedef struct 	_regex_in		pregex_in;


typedef	int 					(*pregex_fn)( pregex*, pregex_range* );
#define PREGEX_FN_NULL			( (pregex_fn)NULL )



#define PREGEX_CCL_MIN			0x0
#if UNICODE
#define PREGEX_CCL_MAX			0xFFFF
#else
#define PREGEX_CCL_MAX			0xFF
#endif

struct _regex_cr
{
	pchar			begin;
	pchar			end;
};

struct _regex_ccl
{
	int				min;
	int				max;

	plist*			ranges;

	char*			str;
};


struct _regex_accept
{
	int				accept;		
	pboolean		greedy;		
	int				anchors;	
};


struct _regex_nfa_st
{
	pregex_ccl*		ccl;		
	pregex_nfa_st*	next;		
	pregex_nfa_st*	next2;		

	int				ref;		

	pregex_accept	accept;		
};


struct _regex_nfa
{
	plist*			states;		
	int				modifiers;	

	int				ref_count;	
	int				ref_cur;	
};


struct _regex_dfa_tr
{
	pregex_ccl*		ccl;		
	unsigned int	go_to;		
};


struct _regex_dfa_st
{
	plist*			trans;		
	pregex_dfa_tr*	def_trans;	
	int*			ref;		
	int				ref_cnt;	

	pregex_accept	accept;		

	pboolean		done;		
	plist*			nfa_set;	
};


struct _regex_dfa
{
	plist*			states;		
	int				ref_count;	
};



struct _regex_ptn
{
	pregex_ptntype	type;		
	pregex_ccl*		ccl;		

	pregex_ptn*		child[ 2 ];	
	pregex_ptn*		next;		

	pregex_accept*	accept;		
};

struct _regex_range
{
	char*			begin;		
	pchar*			pbegin;		
	char*			end;		
	pchar*			pend;		
	psize			pos;		
	psize			len;		
	int				accept;		
	pbyte*			user;		
};


struct _regex
{
	

	short			stat;		
	int				flags;		

	plist*			patterns;	

	union
	{
		pregex_nfa*	nfa;		
		pregex_dfa*	dfa;		
	} machine;

	

	int				age;		

	pregex_fn		match_fn;	

	
	int				last_err;	
	int				match_count;
	int				last_age;	

	char*			last_str;	
	char*			last_pos;	

	pregex_range	range;		
	pregex_range	split;		

	pregex_range*	refs;		
	int				refs_cnt;	

	char*			tmp_str;	
};





#define PGERR( txt )				fprintf( stderr, "%s\n", txt )

typedef struct _pggrammar			pggrammar;
typedef struct _pgproduction		pgproduction;
typedef struct _pgsymbol			pgsymbol;


typedef enum
{
	PGSYMTYPE_UNDEFINED,			
	PGSYMTYPE_TERMINAL,				
	PGSYMTYPE_NONTERMINAL			
} pgsymtype;

typedef enum
{
	PGASSOC_NONE,					
	PGASSOC_LEFT,					
	PGASSOC_RIGHT,					
	PGASSOC_NOASSOC					
} pgassoc;

typedef enum
{
	PGPARADIGM_UNDEFINED,			
	
	PGPARADIGM_LR0,					
	PGPARADIGM_SLR1,				
	PGPARADIGM_LR1,					
	PGPARADIGM_LALR1,				

	PGPARADIGM_LL1,					
	
	PGPARADIGM_EOP					
} pgparadigm;


struct _pgsymbol
{
	pggrammar*		grammar;		

	int				id;				
	pgsymtype		type;			
	char*			name;			

	pboolean		nullable;		

	plist*			first;			
	plist*			follow;			

	
	pregex_ptn*		ptn;			
	pregex_accept	accept;			

	int				prec;			
	pgassoc			assoc;			

	
	plist*			productions;	
};

typedef pgsymbol	pgterminal;		
typedef pgsymbol	pgnonterminal;	


struct _pgproduction
{
	pggrammar*		grammar;		

	int				id;				

	pgsymbol*		lhs;			
	plist*			rhs;			

	int				prec;			
	pgassoc			assoc;			

	plist*			select;			

	char*			strval;			
};


struct _pggrammar
{
	plist*			symbols;		
	plist*			productions;	

	pgnonterminal*	goal;			
	pgterminal*		eoi;			
	pgterminal*		error;			

	pregex_ptn*		whitespace;		
};




typedef struct _pgtoken			pgtoken;
typedef struct _pglexer			pglexer;


struct _pgtoken
{
	int				id;			
	pgsymbol*		symbol;		
	char*			token;		
	int				len;		

	int				row;		
	int				col;		
};


struct _pglexer
{
	pggrammar*		grammar;		
	int				flags;			

#define PLEX_MOD_NONE			0		
#define PLEX_MOD_SKIP_UNKNOWN	1		
#define PLEX_MOD_UTF8			2		
#define PLEX_MOD_WCHAR			4		

	int				states_cnt;		
	pchar**			states;			

	
	int				source;
#define PLEX_SRCTYPE_FUNC		0		
#define PLEX_SRCTYPE_STRING		1		
#define	PLEX_SRCTYPE_STREAM		2		

	union
	{
		char*			str;			
		FILE*			stream;			
		unsigned int	(*func)();		
	} src;							

	pchar			eof;			
	pboolean		is_eof;			

	
	int				chsize;

	pchar*			bufbeg;			
	pchar*			bufend;			
	size_t			bufsiz;			

	char*			lexem;			
	size_t			len;			

#define PLEX_BUFSTEP	1024

	int				line;			
	int				column;			
};



typedef struct _pgparser			pgparser;
typedef struct _pgastnode			pgastnode;


struct _pgparser
{
	pgparadigm		paradigm;	

	pggrammar*		grammar;	
	pglexer*		lexer;		

	plist*			states;		

	pboolean		optimize;	
	char*			source;		
};


struct _pgastnode
{
	pgtoken*		token;			

	pgastnode*		parent;			
	pgastnode*		child;			
	pgastnode*		prev;			
	pgastnode*		next;			
};




#ifdef __cplusplus
extern "C"
{
#endif





void _dbg_trace( char* file, int line, char* type, char* format, ... );


LIST* list_push( LIST* list, void* ptr );
LIST* list_pop( LIST* list, void** ptr );
LIST* list_remove( LIST* list, void* ptr );
LIST* list_free( LIST* list );
void list_print( LIST* list, void (*callback)( void* ) );
LIST* list_dup( LIST* src );
int list_find( LIST* list, void* ptr );
void* list_getptr( LIST* list, int cnt );
int list_diff( LIST* first, LIST* second );
LIST* list_union( LIST* first, LIST* second );
int list_count( LIST* list );
pboolean list_subset( LIST* list, LIST* subset );
LIST* list_sort( LIST* list, int (*sf)( void*, void* ) );


pboolean plist_init( plist* list, psize size, pbyte flags );
plist* plist_create( psize size, pbyte flags );
plist* plist_dup( plist* list );
pboolean plist_erase( plist* list );
pboolean plist_clear( plist* list );
plist* plist_free( plist* list );
plistel* plist_insert( plist* list, plistel* pos, char* key, void* src );
plistel* plist_push( plist* list, void* src );
void* plist_malloc( plist* list );
pboolean plist_remove( plist* list, plistel* e );
pboolean plist_pop( plist* list, void* dest );
plistel* plist_get( plist* list, int n );
plistel* plist_get_by_key( plist* list, char* key );
plistel* plist_get_by_ptr( plist* list, void* ptr );
int plist_union( plist* all, plist* from );
int plist_diff( plist* left, plist* right );
pboolean plist_subsort( plist* list, plistel* from, plistel* to );
pboolean plist_sort( plist* list );
pboolean plist_set_comparefn( plist* list, int (*comparefn)( plist*, plistel*, plistel* ) );
pboolean plist_set_sortfn( plist* list, int (*sortfn)( plist*, plistel*, plistel* ) );
void* plist_access( plistel* e );
char* plist_key( plistel* e );
plistel* plist_next( plistel* u );
plistel* plist_prev( plistel* u );
int plist_offset( plistel* u );
pboolean plist_swap( plistel* a, plistel* b );
plistel* plist_first( plist* l );
plistel* plist_last( plist* l );
int plist_size( plist* l );
int plist_count( plist* l );


void* pmalloc( psize size );
void* prealloc( void* oldptr, psize size );
void* pfree( void* ptr );
void* pmemdup( void* ptr, psize size );


pboolean pstack_init( pstack* stack, size_t size, size_t step );
pstack* pstack_create( size_t size, size_t step );
pboolean pstack_erase( pstack* stack );
pstack* pstack_free( pstack* stack );
void* pstack_push( pstack* stack, void* item );
void* pstack_pop( pstack* stack );
void* pstack_access( pstack* stack, size_t offset );
void* pstack_top( pstack* stack );
void* pstack_bottom( pstack* stack );
int pstack_count( pstack* stack );


pregex_ccl* pregex_ccl_create( int min, int max, char* ccldef );
pboolean pregex_ccl_compat( pregex_ccl* l, pregex_ccl* r );
int pregex_ccl_size( pregex_ccl* ccl );
int pregex_ccl_count( pregex_ccl* ccl );
pregex_ccl* pregex_ccl_dup( pregex_ccl* ccl );
pboolean pregex_ccl_testrange( pregex_ccl* ccl, pchar begin, pchar end );
pboolean pregex_ccl_test( pregex_ccl* ccl, pchar ch );
pboolean pregex_ccl_instest( pregex_ccl* ccl, pchar ch );
pboolean pregex_ccl_addrange( pregex_ccl* ccl, pchar begin, pchar end );
pboolean pregex_ccl_add( pregex_ccl* ccl, pchar ch );
pboolean pregex_ccl_delrange( pregex_ccl* ccl, pchar begin, pchar end );
pboolean pregex_ccl_del( pregex_ccl* ccl, pchar ch );
pboolean pregex_ccl_negate( pregex_ccl* ccl );
pregex_ccl* pregex_ccl_union( pregex_ccl* ccl, pregex_ccl* add );
pregex_ccl* pregex_ccl_diff( pregex_ccl* ccl, pregex_ccl* rem );
int pregex_ccl_compare( pregex_ccl* left, pregex_ccl* right );
pregex_ccl* pregex_ccl_intersect( pregex_ccl* ccl, pregex_ccl* within );
pboolean pregex_ccl_get( pchar* from, pchar* to, pregex_ccl* ccl, int offset );
pboolean pregex_ccl_parse( pregex_ccl* ccl, char* ccldef, pboolean extend );
pboolean pregex_ccl_erase( pregex_ccl* ccl );
pregex_ccl* pregex_ccl_free( pregex_ccl* ccl );
char* pregex_ccl_to_str( pregex_ccl* ccl, pboolean escape );
void pregex_ccl_print( FILE* stream, pregex_ccl* ccl, int break_after );


void pregex_dfa_print( pregex_dfa* dfa );
pregex_dfa* pregex_dfa_create( void );
pboolean pregex_dfa_reset( pregex_dfa* dfa );
pregex_dfa* pregex_dfa_free( pregex_dfa* dfa );
int pregex_dfa_from_nfa( pregex_dfa* dfa, pregex_nfa* nfa );
int pregex_dfa_minimize( pregex_dfa* dfa );
int pregex_dfa_match( pregex_dfa* dfa, char* str, size_t* len, int* anchors, pregex_range** ref, int* ref_count, int flags );
int pregex_dfa_to_matrix( pchar*** matrix, pregex_dfa* dfa );


int pregex_qmatch( char* regex, char* str, int flags, pregex_range** results );
int pregex_qsplit( char* regex, char* str, int flags, pregex_range** results );
char* pregex_qreplace( char* regex, char* str, char* replace, int flags );


pregex_accept* pregex_accept_init( pregex_accept* accept );
pboolean pregex_check_anchors( char* all, char* str, psize len, int anchors, int flags );


pregex_nfa_st* pregex_nfa_create_state( pregex_nfa* nfa, char* chardef, int flags );
void pregex_nfa_print( pregex_nfa* nfa );
pregex_nfa* pregex_nfa_create( void );
pboolean pregex_nfa_reset( pregex_nfa* nfa );
pregex_nfa* pregex_nfa_free( pregex_nfa* nfa );
int pregex_nfa_move( pregex_nfa* nfa, plist* hits, pchar from, pchar to );
int pregex_nfa_epsilon_closure( pregex_nfa* nfa, plist* closure, pregex_accept* accept );
int pregex_nfa_match( pregex_nfa* nfa, char* str, psize* len, int* anchors, pregex_range** ref, int* ref_count, int flags );
int pregex_nfa_from_string( pregex_nfa* nfa, char* str, int flags, int acc );


pregex_ptn* pregex_ptn_create_char( pregex_ccl* ccl );
pregex_ptn* pregex_ptn_create_string( char* str, int flags );
pregex_ptn* pregex_ptn_create_sub( pregex_ptn* ptn );
pregex_ptn* pregex_ptn_create_alt( pregex_ptn* left, ... );
pregex_ptn* pregex_ptn_create_kle( pregex_ptn* ptn );
pregex_ptn* pregex_ptn_create_pos( pregex_ptn* ptn );
pregex_ptn* pregex_ptn_create_opt( pregex_ptn* ptn );
pregex_ptn* pregex_ptn_create_seq( pregex_ptn* first, ... );
pregex_ptn* pregex_ptn_free( pregex_ptn* ptn );
void pregex_ptn_print( pregex_ptn* ptn, int rec );
int pregex_ptn_to_regex( char** regex, pregex_ptn* ptn );
int pregex_ptn_to_nfa( pregex_nfa* nfa, pregex_ptn* pattern );
int pregex_ptn_parse( pregex_ptn** ptn, char* str, int flags );


pregex* pregex_create( void );
pregex* pregex_free( pregex* regex );
pregex* pregex_reset( pregex* regex );
int pregex_compile( pregex* regex, char* pattern, int accept );
int pregex_finalize( pregex* regex );
pregex_range* pregex_match_next( pregex* regex, char* str );
int pregex_match( pregex* regex, char* str, pregex_range** results );
pregex_range* pregex_split_next( pregex* regex, char* str );
int pregex_split( pregex* regex, char* str, pregex_range** results );
char* pregex_replace( pregex* regex, char* str, char* replacement );
pregex_range* pregex_get_range( pregex* regex );
pregex_range* pregex_get_split( pregex* regex );
pregex_range* pregex_get_ref( pregex* regex, int offset );
int pregex_get_match_count( pregex* regex );
int pregex_get_flags( pregex* regex );
pboolean pregex_set_flags( pregex* regex, int flags );
pregex_fn pregex_get_match_fn( pregex* regex );
pboolean pregex_set_match_fn( pregex* regex, pregex_fn match_fn );


char* pregex_range_to_string( pregex_range* range );


int pregex_ref_init( pregex_range** ref, int* ref_count, int ref_all, int flags );
void pregex_ref_update( pregex_range* ref, char* strp, psize off );


char* wchar_to_u8( pchar* str, pboolean freestr );
pchar* u8_to_wchar( char* str, pboolean freestr );
char* plong_to_uchar( plong l );
pchar* plong_to_pchar( plong l );
char* pulong_to_uchar( pulong ul );
pchar* pulong_to_pchar( pulong ul );
char* pdouble_to_uchar( pdouble d );
pchar* pdouble_to_pchar( pdouble d );


char* pstrcatchar( char* str, wchar chr );
char* pstrcatstr( char* dest, char* src, boolean freesrc );
char* pstrncatstr( char* str, char* append, psize n );
char* pstrreplace( char* str, char* find, char* replace );
char* pstrdup( char* str );
char* pstrndup( char* str, psize len );
psize pstrlen( char* str );
int psprintf( char* res, char* fmt, ... );
int pvasprintf( char** str, char* fmt, va_list ap );
char* pasprintf( char* fmt, ... );
char* psetstr( char** str, char* val );
char* pgetstr( char* str );
char* pstrrender( char* tpl, ... );
char* pstrltrim( char* s );
char* pstrrtrim( char* s );
char* pstrtrim( char* s );
int pstrsplit( char*** tokens, char* str, char* sep, int limit );
char* pstrupr( char* s );
char* pstrlwr( char* s );
int pstrcasecmp( char* s1, char* s2 );
int pstrncasecmp( char* s1, char* s2, pint n );
int pstrparsechar( wchar* retc, char *str, pboolean escapeseq );
#ifdef UNICODE
pchar* pwcsdup( pchar* str );
int pwcsprintf( pchar* res, pchar* fmt, ... );
int pvawcsprintf( pchar** str, pchar* fmt, va_list ap );
pchar* pawcsprintf( pchar* fmt, ... );
pchar* pwcscatchar( pchar* str, wchar chr );
pchar* pwcscatstr( pchar* dest, pchar* src, boolean freesrc );
pchar* pwcsncatstr( pchar* str, pchar* append, psize num );
psize pwcslen( pchar* str );
#endif


pboolean u8_isutf( pbyte c );
int u8_seqlen(char *s);
wchar u8_char( char* str );
char* u8_move( char* str, int count );
wchar u8_parse_char( char** ch );
int u8_toucs(wchar *dest, int sz, char *src, int srcsz);
int u8_toutf8(char *dest, int sz, wchar *src, int srcsz);
int u8_wc_toutf8(char *dest, wchar ch);
int u8_offset(char *str, int charnum);
int u8_charnum(char *s, int offset);
int u8_strlen(char *s);
wchar u8_nextchar(char *s, int *i);
void u8_inc(char *s, int *i);
void u8_dec(char *s, int *i);
int octal_digit(char c);
int hex_digit(char c);
int u8_read_escape_sequence(char *str, wchar *dest);
int u8_unescape(char *buf, int sz, char *src);
int u8_escape_wchar(char *buf, int sz, wchar ch);
int u8_escape(char *buf, int sz, char *src, int escape_quotes);
char *u8_strchr(char *s, wchar ch, int *charn);
char *u8_memchr(char *s, wchar ch, size_t sz, int *charn);
int u8_is_locale_utf8(char *locale);


char* pwhich( char* filename, char* directories );
char* pbasename( char* path );
pboolean pfileexists( char* filename );
int map_file( char** cont, char* filename );
pint pgetopt( char* opt, char** param, pint* next, pint argc, char** argv, char* optstr, char* loptstr, pint idx );


pboolean punion_init( punion* var );
punion* punion_create( void );
pboolean punion_reset( punion* var );
punion* punion_free( punion* u );


pbyte punion_to_byte( punion* var );
char punion_to_char( punion* var );
pint punion_to_int( punion* var );
plong punion_to_long( punion* var );
pulong punion_to_ulong( punion* var );
pfloat punion_to_float( punion* var );
pdouble punion_to_double( punion* var );
char* punion_to_string( punion* var );
pchar* punion_to_wstring( punion* var );
pint punion_convert( punion* var, pbyte type );


pbyte punion_get_byte( punion* var );
char punion_get_char( punion* var );
pint punion_get_int( punion* var );
plong punion_get_long( punion* var );
pulong punion_get_ulong( punion* var );
pfloat punion_get_float( punion* var );
pdouble punion_get_double( punion* var );
char* punion_get_cstring( punion* var );
char* punion_get_string( punion* var );
pchar* punion_get_wcstring( punion* var );
pchar* punion_get_wstring( punion* var );


pbyte punion_set_byte( punion* var, pbyte b );
char punion_set_char( punion* var, char c );
pint punion_set_int( punion* var, pint i );
plong punion_set_long( punion* var, plong l );
pulong punion_set_ulong( punion* var, pulong ul );
pfloat punion_set_float( punion* var, pfloat f );
pdouble punion_set_double( punion* var, pdouble d );
char* punion_set_cstring( punion* var, char* s );
char* punion_set_string( punion* var, char* s );
pchar* punion_set_wcstring( punion* var, pchar* ws );
pchar* punion_set_wstring( punion* var, pchar* ws );


XML_T xml_child( XML_T xml, char* name );
XML_T xml_idx( XML_T xml, int idx );
char* xml_attr( XML_T xml, char* attr );
plong xml_int_attr( XML_T xml, char* attr );
pdouble xml_float_attr( XML_T xml, char* attr );
XML_T xml_vget( XML_T xml, va_list ap );
XML_T xml_get( XML_T xml, ... );
char ** xml_pi( XML_T xml, char* target );
char* xml_decode( char* s, char ** ent, char t );
char* xml_str2utf8( char ** s, size_t* len );
void xml_free_attr( char ** attr );
XML_T xml_parse_str( char* s, size_t len );
XML_T xml_parse_fp( FILE* fp );
XML_T xml_parse_file( char* file );
char* xml_ampencode( char* s, size_t len, char ** dst, size_t* dlen, size_t* max, short a );
char* xml_toxml( XML_T xml );
void xml_free( XML_T xml );
char* xml_error( XML_T xml );
XML_T xml_new( char* name );
XML_T xml_insert( XML_T xml, XML_T dest, size_t off );
XML_T xml_add_child( XML_T xml, char* name, size_t off );
XML_T xml_set_txt( XML_T xml, char* txt );
XML_T xml_set_attr( XML_T xml, char* name, char* value );
XML_T xml_set_int_attr( XML_T xml, char* name, plong value );
XML_T xml_set_float_attr( XML_T xml, char* name, pdouble value );
XML_T xml_set_flag( XML_T xml, short flag );
int xml_count( XML_T xml );
int xml_count_all( XML_T xml );
XML_T xml_cut( XML_T xml );


pggrammar* pg_grammar_create( void );
pggrammar* pg_grammar_free( pggrammar* g );
void pg_grammar_print( pggrammar* g );
BOOLEAN pg_grammar_compute_first( pggrammar* g );
BOOLEAN pg_grammar_compute_follow( pggrammar* g );
BOOLEAN pg_grammar_compute_select( pggrammar* g );
pgterminal* pg_grammar_get_goal( pggrammar* g );
BOOLEAN pg_grammar_set_goal( pggrammar* g, pgnonterminal* goal );
pgterminal* pg_grammar_get_eoi( pggrammar* g );
BOOLEAN pg_grammar_set_eoi( pggrammar* g, pgterminal* eoi );
BOOLEAN pg_grammar_parse_whitespace( pggrammar* grammar, char* str );
BOOLEAN pg_grammar_set_whitespace( pggrammar* grammar, pregex_ptn* whitespace );
pregex_ptn* pg_grammar_get_whitespace( pggrammar* grammar );


pgnonterminal* pg_nonterminal_create( pggrammar* grammar, char* name );
pgnonterminal* pg_nonterminal_drop( pgterminal* nonterminal );
pgnonterminal* pg_nonterminal_get( pggrammar* g, int offset );


pgproduction* pg_production_create( pgnonterminal* lhs, ... );
pgproduction* pg_production_drop( pgproduction* p );
char* pg_production_to_string( pgproduction* p );
void pg_production_print( pgproduction* p, FILE* f );
pboolean pg_production_append( pgproduction* p, pgsymbol* sym );
pgproduction* pg_production_get( pggrammar* grammar, int i );
pgproduction* pg_production_get_by_lhs( pgnonterminal* lhs, int i );
pgsymbol* pg_production_get_rhs( pgproduction* p, int i );
int pg_production_get_id( pgproduction* p );
pggrammar* pg_production_get_grammar( pgproduction* p );
pgnonterminal* pg_production_get_lhs( pgproduction* p );
int pg_production_get_rhs_length( pgproduction* p );


pgsymbol* pg_symbol_create( pggrammar* grammar, pgsymtype type, char* name );
pgsymbol* pg_symbol_free( pgsymbol* symbol );
BOOLEAN pg_symbol_reset( pgsymbol* s );
void pg_symbol_print( pgsymbol* symbol, FILE* f );
BOOLEAN pg_symbol_is_terminal( pgsymbol* symbol );
BOOLEAN pg_symbol_is_nonterminal( pgsymbol* symbol );
pgsymbol* pg_symbol_get( pggrammar* g, int i );
int pg_symbol_get_id( pgsymbol* s );
pgsymtype pg_symbol_get_type( pgsymbol* s );
pggrammar* pg_symbol_get_grammar( pgsymbol* s );
char* pg_symbol_get_name( pgsymbol* s );


pgterminal* pg_terminal_create( pggrammar* grammar, char* name, char* pattern );
pgterminal* pg_terminal_drop( pgterminal* terminal );
pgterminal* pg_terminal_get( pggrammar* g, int offset );
BOOLEAN pg_terminal_parse_pattern( pgterminal* terminal, char* pattern );
BOOLEAN pg_terminal_set_pattern( pgterminal* terminal, pregex_ptn* ptn );
pregex_ptn* pg_terminal_get_pattern( pgterminal* terminal );


pglexer* pg_lexer_create( pgparser* parser );
pboolean pg_lexer_reset( pglexer* lex );
pglexer* pg_lexer_free( pglexer* lex );
pboolean pg_lexer_set_source( pglexer* lex, int type, void* ptr );
pboolean pg_lexer_fetch( pglexer* lex );


BOOLEAN pg_parser_lr_closure( pgparser* parser );
BOOLEAN pg_parser_lr_reset( pgparser* parser );


pboolean pg_parser_lr_eval( pgparser* parser, char* input );


pgparser* pg_parser_create( pggrammar* grammar, pgparadigm paradigm );
pgparser* pg_parser_free( pgparser* parser );
BOOLEAN pg_parser_generate( pgparser* p );
BOOLEAN pg_parser_run( pgparser* p );
BOOLEAN pg_parser_is_lr( pgparser* p );
BOOLEAN pg_parser_is_ll( pgparser* p );
pggrammar* pg_parser_get_grammar( pgparser* p );
pboolean pg_parser_get_optimize( pgparser* p );
pboolean pg_parser_set_optimize( pgparser* p, pboolean optimize );
char* pg_parser_get_source( pgparser* p );
pboolean pg_parser_set_source( pgparser* p, char* source );


#ifdef __cplusplus
}
#endif

#endif 

