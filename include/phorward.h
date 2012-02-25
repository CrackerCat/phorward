/*
	This file was automatically generated by /home/neo/Phorward/src/phorward/src/../run/pinclude.
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
typedef unsigned int			wchar;
#endif


typedef char					pbyte;		
typedef wchar					pchar;		
typedef char					uchar;		
typedef	int						pint;		
typedef	float					pfloat;		
typedef double					pdouble;	
typedef long					plong;		
typedef size_t					pulong;		
typedef size_t					psize;		

typedef int 					pboolean;	
#define BOOLEAN					pboolean
#define boolean 				pboolean

#define BOOLEAN_STR( b ) ( ( b ) ? "TRUE" : "FALSE" )

#define TRUE	1
#define FALSE	0


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


#ifndef _WIN32
#define PPATHSEP				'/'
#else
#define PPATHSEP				'\\'
#endif


#define bit_set( val, bit )		( (val) |= (bit) )
#define bit_unset( val, bit )	( (val) &= ~(bit) )
#define bit_is_set( val, bit )	( ( (val) & (bit) ) == (bit) )
#define bit_is_unset( val, bit ) \
 								( ( (val) & (bit) ) == 0 )






#ifndef BITSET_H
#define BITSET_H


typedef uchar byte;
typedef byte* bitset;


#define bitset_free( set ) 		free( set )

#endif



#ifndef _DBG_H
#define _DBG_H




#ifndef __DBG_LOCAL_COMPILE
	#ifdef __WITH_TRACE
		extern int _dbg_indent;
		extern FILE* _dbg_tracefile;
	#endif
#endif






#ifdef __WITH_TRACE
	#define MAIN( tracefile ) \
		char*	_dbg_proc_name	= "main"; \
		do { \
		_dbg_tracefile = fopen( tracefile, "at" ); \
		_dbg_indent++; \
		_dbg_trace( _dbg_tracefile, _dbg_indent, __FILE__, __LINE__, \
			_dbg_proc_name, "ENTRY ", "" ); \
		} \
		while( 0 )
#else
	#define MAIN( tracefile )
#endif




#ifdef __WITH_TRACE
	#define PROC( name ) \
		char*	_dbg_proc_name	= name; \
		do { \
		_dbg_indent++; \
		_dbg_trace( _dbg_tracefile, _dbg_indent, __FILE__, __LINE__, \
			_dbg_proc_name, "ENTRY ", "" ); \
		} \
		while( 0 )
#else
	#define PROC( name )
#endif



#ifdef __WITH_TRACE
	#define RETURN( val ) \
		do \
		{ _dbg_trace( _dbg_tracefile, _dbg_indent, __FILE__, __LINE__, \
			_dbg_proc_name, "RETURN", "", val );\
		_dbg_indent--; \
		return val; \
		} \
		while( 0 )
#else
	#define RETURN( val ) \
		return val
#endif



#ifdef __WITH_TRACE
	#define VOIDRET \
		do \
		{ \
		_dbg_trace( _dbg_tracefile, _dbg_indent, __FILE__, __LINE__, \
			_dbg_proc_name, "RETURN", "(void)" ); \
		_dbg_indent--; \
		return; \
		} \
		while( 0 )
#else
	#define VOIDRET \
		return
#endif


#ifdef __WITH_TRACE
	#define MAINRET( val ) \
		do \
		{ \
		_dbg_trace( _dbg_tracefile, _dbg_indent, __FILE__, __LINE__, \
			_dbg_proc_name, "RETURN", ">%d<", val ); \
		_dbg_indent--; \
		fclose( _dbg_tracefile ); \
		return val; \
		} \
		while( 0 )
#else
	#define MAINRET( val )\
		return val
#endif



#ifdef __WITH_TRACE
	#define MSG( text ) \
		_dbg_trace( _dbg_tracefile, _dbg_indent, __FILE__, __LINE__, \
			_dbg_proc_name, "MSG   ", "%s", text )
#else
	#define MSG( text )
#endif



#ifdef __WITH_TRACE
	#define VARS( name, format, val ) \
		_dbg_trace( _dbg_tracefile, _dbg_indent, __FILE__, __LINE__, \
			_dbg_proc_name, "VARS  ", "%s = >" format "<", name, val )
#else
	#define VARS( name, format, val )
#endif



#ifdef __WITH_TRACE
	#define PARMS( name, format, val ) \
		_dbg_trace( _dbg_tracefile, _dbg_indent, __FILE__, __LINE__, \
			_dbg_proc_name, "PARMS ", "%s = >" format "<", name, val )
#else
	#define PARMS( name, format, val )
#endif


#ifdef __WITH_TRACE
	#define TIMEDUMP \
		_dbg_time( _dbg_tracefile, _dbg_indent, __FILE__, __LINE__, \
			_dbg_proc_name )
#else
	#define TIMEDUMP
#endif

#endif



#ifndef LLIST_H
#define LLIST_H


typedef struct llist
{
	void*			pptr;
	struct llist*	next;
} LIST;


#define listPush				list_push
#define listPop					list_pop
#define listRemove				list_remove
#define listFree				list_free
#define listPrint				list_print
#define listDup					list_dup
#define listFind				list_find
#define listGetPtrByPosition	list_getptr
#define listDiff				list_diff
#define listUnion				list_union
#define listCount				list_count
#define listSubset				list_subset


#define list_access( ll )		( (ll) ? (ll)->pptr : (void*)NULL )
#define list_next( ll )			( (ll) ? (ll)->next : (LIST*)NULL )
#define list_replace( ll, ptr )	( (ll) ? (ll)->pptr = (ptr) : 0 )

#define LISTFOR( ll, cc )		for( (cc) = (ll); (cc); (cc) = list_next(cc) )

#endif




#ifndef __HASHTAB_H
#define __HASHTAB_H


#define HASHTAB_MOD_NONE		0	
#define HASHTAB_MOD_EXTKEYS		1	
#define HASHTAB_MOD_WCHAR		2	
#define HASHTAB_MOD_LIST		4	
#define HASHTAB_MOD_NO_COLL		8	

#define HASHTAB_CALLBACK		void(*) ( void* )
#define HASHTAB_NO_CALLBACK		( (HASHTAB_CALLBACK) NULL )


typedef struct _hashtab 	HASHTAB;
typedef struct _bucket		BUCKET;
typedef struct _hashelem	HASHELEM;


struct _hashtab
{
	int			flags;					
	int			size;					
	BUCKET*		buckets;				
	HASHELEM*	discarded;				
	LIST*		list;					
};

#define hashtab_list( ht )				(ht)->list

struct _bucket
{
	HASHELEM*	start;					
	HASHELEM*	end;					
};

struct _hashelem
{
	uchar*		key;					
	void*		data;					
	HASHELEM*	prev;					
	HASHELEM*	next;					
};

#endif




#ifndef STACK_H
#define STACK_H

typedef struct
{
	pbyte*	stack;
	psize	size;
	psize	top;
	psize	count;
	psize	step;
} STACK;

#define STACK_CALLBACK		void(*) ( pbyte* )
#define STACK_NO_CALLBACK	( (STACK_CALLBACK)NULL )

#define stack_count( s )	( s )->top

#endif



#ifndef CCL_H
#define CCL_H


#define CCL_MIN			0x0

#ifdef UTF8
#define CCL_MAX			0xffff
#else
#define CCL_MAX			0xff
#endif


typedef struct _crange	CRANGE;
typedef struct _crange*	CCL;

struct _crange
{
	pchar	begin;
	pchar	end;
};


#define ccl_free( ccl )				(CCL)pfree( ccl )
#define ccl_replace( ccl, nccl )	ccl_free( ccl ), ccl = nccl
#define ccl_end( ccl )				( (ccl)->begin == CCL_MAX )

#endif




#define REGEX_ACCEPT_NONE		-1

#define REGEX_ALLOC_STEP		16


#define REGEX_STAT_NONE			0
#define REGEX_STAT_NFA			1
#define REGEX_STAT_DFA			2


#define REGEX_MOD_NONE			0	
#define REGEX_MOD_WCHAR			1	
#define REGEX_MOD_INSENSITIVE	2	
#define REGEX_MOD_GLOBAL		4	
#define REGEX_MOD_STATIC_STRING	8	
#define REGEX_MOD_NO_REFERENCES	16	
#define REGEX_MOD_NO_ERRORS		32	
#define REGEX_MOD_NO_ANCHORS	64	
#define REGEX_MOD_GREEDY		128	
#define REGEX_MOD_NONGREEDY		256	


#define REGEX_ANCHOR_NONE		0	
#define REGEX_ANCHOR_BOL		1	
#define REGEX_ANCHOR_EOL		2	
#define REGEX_ANCHOR_BOW		4	
#define REGEX_ANCHOR_EOW		8	

#ifndef PRIVATE
#define PRIVATE static
#endif


typedef CCL						pregex_ccl;

typedef struct	_regex_accept	pregex_accept;

typedef struct	_regex_nfa_st	pregex_nfa_st;
typedef struct	_regex_dfa_tr	pregex_dfa_tr;
typedef struct	_regex_dfa_st	pregex_dfa_st;
typedef struct	_regex_nfa		pregex_nfa;
typedef struct	_regex_dfa		pregex_dfa;

typedef enum 	_regex_ptntype	pregex_ptntype;
typedef struct	_regex_ptn		pregex_ptn;
typedef struct	_regex_ptndef	pregex_ptndef;

typedef struct	_regex			pregex;
typedef	struct	_regex_result	pregex_result;


typedef	int 					(*pregex_callback)( pregex_result* );
#define REGEX_NO_CALLBACK		( (pregex_callback)NULL )




struct _regex_accept
{
	int				accept;		
	BOOLEAN			greedy;		
	int				anchors;	
};

struct _regex_nfa_st
{
	pregex_ccl		ccl;		
	pregex_nfa_st*	next;		
	pregex_nfa_st*	next2;		

	int				ref;		
	
	pregex_accept	accept;		
};

struct _regex_nfa
{	
	LIST*			states;		
	LIST*			empty;		
	pbyte			modifiers;	
	
	int				ref_count;	
	int				ref_cur;	
};

struct _regex_dfa_tr
{
	pregex_ccl		ccl;		
	unsigned int	go_to;		
};

struct _regex_dfa_st
{
	LIST*			trans;		
	pregex_dfa_tr*	def_trans;	
	int*			ref;		
	int				ref_cnt;	

	pregex_accept	accept;		

	BOOLEAN			done;		
	LIST*			nfa_set;	
};

struct _regex_dfa
{
	LIST*			states;		
	int				ref_count;	
};



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

struct _regex_ptn
{
	pregex_ptntype	type;		
	CCL				ccl;		
	
	pregex_ptn*		child[ 2 ];	
	pregex_ptn*		next;		
};

struct _regex_ptndef
{
	pregex_ptn*		pattern;	
	pregex_accept	accept;		
};

struct _regex
{
	pbyte			stat;		

	LIST*			defs;		
	union
	{
		pregex_nfa	nfa;		
		pregex_dfa	dfa;		
	} machine;

	int				flags;		
};

struct _regex_result
{
	uchar*			begin;		
	pchar*			pbegin;		
	uchar*			end;		
	pchar*			pend;		
	psize			pos;		
	psize			len;		
	int				accept;		
	pbyte*			user;		
};




#ifndef STRING_H
#define STRING_H


#ifdef UNICODE

#define Pstrcpy					wcscpy
#define Pstrcat					wcscat
#define Pstrncpy				wcsncpy
#define Pstrcmp					wcscmp
#define Pstrncmp				wcsncmp	
#define Pstrtol					wcstol
#define Pstrtoul				wcstoul
#define Pstrtod					wcstod
#define Pstrstr					wcsstr
#define Pstrchr					wcschr
#define Pstrrchr				wcsrchr

#define Pisupper				iswupper
#define Pislower				iswlower
#define Ptoupper				towupper
#define Ptolower				towlower
#define Pisdigit				iswdigit
#define Pisblank				iswblank
#define Pisalnum				iswalnum
#define Pisalpha				iswalpha

#else


#define Pstrlen					pstrlen
#define Pstrcpy					pstrcpy
#define Pstrcat					pstrcat
#define Pstrncpy				pstrncpy
#define Pstrcmp					pstrcmp
#define Pstrncmp				pstrncmp
#define Pstrtol					pstrtol
#define Pstrtoul				pstrtoul
#define Pstrtod					pstrtoud
#define Pstrchr					pstrchr
#define Pstrrchr				pstrrchr
#define Pstrstr					pstrstr

#define Pisupper				pisupper
#define Pislower				pislower
#define Ptoupper				ptoupper
#define Ptolower				ptolower
#define Pisdigit				pisdigit
#define Pisblank				pisblank
#define Pisalnum				pisalnum
#define Pisalpha				pisalpha


#define Pstrlen					pstrlen
#define Psprintf				psprintf
#define Pstrdup					pstrdup
#define Pstr_append_str			pstr_append_str
#define Pstr_append_char 		pstr_append_char
#define Pstr_append_nchar 		pstr_append_nchar
#define Pvasprintf				pvasprintf
#define Pasprintf				pasprintf

#endif


#define pstrcmp( s1, s2 )		strcmp( pstrzero( s1 ), pstrzero( s2 ) )
#define pstrncmp( s1, s2, n )	strncmp( pstrzero( s1 ), pstrzero( s2 ), n )
#define pstrcpy( s1, s2 )		strcpy( s1, pstrzero( s2 ) )
#define pstrncpy( s1, s2, n )	strncpy( s1, pstrzero( s2 ), n )
#define pstrstr( s1, s2 )		strstr( s1, pstrzero( s2 ) )
#define pstrtok( s1, s2 )		strtok( s1, s2 )
#define pstrchr( s1, ch )		strchr( s1, ch )
#define pstrrchr( s1, ch )		strrchr( s1, ch )
#define pstrcat( s1, s2 )		strcat( s1, s2 )
#define pstrtol( s, p, b )		strtol( s, p, b )
#define pstrtoul( s, p, b )		strtoul( s, p, b )
#define pstrtod( s, p )			strtod( s, p )

#define pisupper( c )			isupper( c )
#define pislower( c )			islower( c )
#define ptoupper( c )			toupper( c )
#define ptolower( c )			tolower( c )
#define pisdigit( c )			isdigit( c )
#define pisblank( c )			isblank( c )
#define pisalnum( c )			isalnum( c )
#define pisalpha( c )			isalpha( c )

#endif



#ifndef UTF8_H
#define UTF8_H


#define u8_isutf(c) (((c)&0xC0)!=0x80)

#endif



#ifndef VAR_H
#define VAR_H


#define PVAR_NULL			0	
#define PVAR_BYTE			1
#define PVAR_CHAR			2
#define PVAR_INT			3
#define PVAR_LONG			4
#define PVAR_ULONG			5
#define PVAR_FLOAT			6
#define PVAR_DOUBLE			7
#define PVAR_STRING			8
#define PVAR_WSTRING		9

#define PVAR_IS_CONSTANT	16	
#define PVAR_IS_CONVERT		32	


typedef struct 
{
	pbyte		type;

	union
	{
		pbyte	b;
		

		uchar	c;
		

		pint	i;
		

		plong	l;
		

		pulong	ul;
		

		pfloat	f;
		

		pdouble	d;
		

		uchar*	s;
		
		

		pchar*	ws;
		
		
	} val;
} pvar;


#define pvar_set_string_d( var, val ) \
			pvar_set_string( var, pstrdup( val ) )
#define pvar_set_wstring_d( var, val ) \
			pvar_set_wstring( var, Pstrdup( val ) )

#define pvar_set_constant( var ) \
			bit_set( (var)->type, PVAR_IS_CONSTANT )
#define pvar_unset_constant( var ) \
			bit_unset( (var)->type, PVAR_IS_CONSTANT )
#define pvar_set_convertible( var ) \
			bit_set( (var)->type, PVAR_IS_CONVERT )
#define pvar_unset_convertible( var ) \
			bit_unset( (var)->type, PVAR_IS_CONVERT )

#define pvar_type( var ) \
			( ( var )->type & 0x0F )
#define pvar_is_constant( var ) \
			( ( var )->type & PVAR_IS_CONSTANT )
#define pvar_is_convertible( var ) \
			( ( var )->type & PVAR_IS_CONVERT )

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
	uchar*		name;		
	uchar **	 attr;		
	uchar*		txt;		
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






bitset bitset_create( int size );
int bitset_set( bitset set, int bit, int state );
int bitset_get( bitset set, int bit );
bitset bitset_copy( int size, bitset source );


void _dbg_trace( FILE* f, int indent, char* file, int line, char* proc, char* type, char* format, ... );
void _dbg_time( FILE* f, int indent, char* file, int line, char* proc );


pint hashtab_init( HASHTAB* ht, pint size, pint flags );
pint hashtab_free( HASHTAB* hashtab, void (*freefct)(void*) );
HASHELEM* hashtab_insert( HASHTAB* hashtab, uchar* key, void* data );
HASHELEM* hashtab_get( HASHTAB* hashtab, uchar* key );
HASHELEM* hashtab_update( HASHTAB* hashtab, uchar* key, void* data );
HASHELEM* hashtab_discard( HASHTAB* hashtab, uchar* key, void (*freefct)(void*) );
pint hashtab_delete( HASHTAB* hashtab, uchar* key, void (*freefct)(void*) );
void hashtab_print( HASHTAB* hashtab, FILE* channel );
pint hashtab_count( HASHTAB* hashtab );
HASHELEM* hashtab_fetch( HASHTAB* hashtab, HASHELEM* current );
void* hashelem_access( HASHELEM* hashelem );
uchar* hashelem_key( HASHELEM* hashelem );
HASHELEM* hashelem_next( HASHELEM* hashelem );
HASHELEM* hashelem_prev( HASHELEM* hashelem );


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
int list_subset( LIST* list, LIST* subset );
LIST* list_sort( LIST* list, int (*sf)( void*, void* ) );


void* pmalloc( psize size );
void* prealloc( void* oldptr, psize size );
void* pfree( void* ptr );
void* pmemdup( void* ptr, psize size );


void stack_init( STACK* stack, psize size, psize step );
void stack_free( STACK* stack, void (*ff)( pbyte* ) );
pbyte* stack_push( STACK* stack, pbyte* item );
pbyte* stack_pop( STACK* stack );
pbyte* stack_access( STACK* stack, psize offset );
void stack_dump( uchar* file, int line, uchar* name, STACK* stack, void (*pf)( pbyte* ) );


int ccl_size( CCL ccl );
int ccl_count( CCL ccl );
CCL ccl_dup( CCL ccl );
CCL ccl_negate( CCL ccl );
CCL ccl_union( CCL first, CCL second );
CCL ccl_create( uchar* ccldef );
void ccl_print( FILE* stream, CCL ccl, int break_after );
uchar* ccl_to_str( CCL ccl, pboolean escape );
CCL ccl_addrange( CCL ccl, pchar begin, pchar end );
CCL ccl_delrange( CCL ccl, pchar begin, pchar end );
CCL ccl_add( CCL ccl, pchar ch );
#if 0
CCL ccl_del( CCL ccl, pchar ch );
#endif
pboolean ccl_test( CCL ccl, pchar ch );
pboolean ccl_testrange( CCL ccl, pchar begin, pchar end );
pboolean ccl_instest( CCL ccl, pchar ch );
int ccl_compare( CCL first, CCL second );
CCL ccl_intersect( CCL first, CCL second );
CCL ccl_diff( CCL first, CCL second );


void pregex_init( pregex* regex, int flags );
int pregex_compile( pregex* regex, uchar* pattern, int accept );
int pregex_finalize( pregex* regex );
void pregex_free( pregex* regex );
int pregex_match( pregex* regex, uchar* str, pregex_callback fn, pregex_result** results );
int pregex_split( pregex* regex, uchar* str, pregex_callback fn, pregex_result** results );
int pregex_replace( pregex* regex, uchar* str, uchar* replacement, pregex_callback fn, uchar** result );


void pregex_dfa_print( FILE* stream, pregex_dfa* dfa );
void pregex_dfa_free( pregex_dfa* dfa );
int pregex_dfa_from_nfa( pregex_dfa* dfa, pregex_nfa* nfa );
int pregex_dfa_minimize( pregex_dfa* dfa );
int pregex_dfa_match( pregex_dfa* dfa, uchar* str, size_t* len, int* anchors, pregex_result** ref, int* ref_count, int flags );


int pregex_qmatch( uchar* regex, uchar* str, int flags, pregex_result** results );
int pregex_qsplit( uchar* regex, uchar* str, int flags, pregex_result** results );
int pregex_qreplace( uchar* regex, uchar* str, uchar* replacement, int flags, uchar** result );


pregex_accept* pregex_accept_init( pregex_accept* accept );
pboolean pregex_check_anchors( uchar* all, uchar* str, psize len, int anchors, int flags );


pregex_nfa_st* pregex_nfa_create_state( pregex_nfa* nfa, uchar* chardef, int flags );
void pregex_nfa_print( pregex_nfa* nfa );
void pregex_nfa_free( pregex_nfa* nfa );
LIST* pregex_nfa_move( pregex_nfa* nfa, LIST* input, pchar from, pchar to );
LIST* pregex_nfa_epsilon_closure( pregex_nfa* nfa, LIST* input, pregex_accept* accept );
int pregex_nfa_match( pregex_nfa* nfa, uchar* str, psize* len, int* anchors, pregex_result** ref, int* ref_count, int flags );
int pregex_nfa_from_string( pregex_nfa* nfa, uchar* str, int flags, int acc );


pregex_ptn* pregex_ptn_create_char( CCL ccl );
pregex_ptn* pregex_ptn_create_string( uchar* str, int flags );
pregex_ptn* pregex_ptn_create_sub( pregex_ptn* ptn );
pregex_ptn* pregex_ptn_create_alt( pregex_ptn* left, ... );
pregex_ptn* pregex_ptn_create_kle( pregex_ptn* ptn );
pregex_ptn* pregex_ptn_create_pos( pregex_ptn* ptn );
pregex_ptn* pregex_ptn_create_opt( pregex_ptn* ptn );
pregex_ptn* pregex_ptn_create_seq( pregex_ptn* first, ... );
pregex_ptn* pregex_ptn_free( pregex_ptn* ptn );
void pregex_ptn_print( pregex_ptn* ptn, int rec );
int pregex_ptn_to_regex( uchar** regex, pregex_ptn* ptn );
int pregex_ptn_to_nfa( pregex_nfa* nfa, pregex_ptn* pattern, pregex_accept* accept );
int pregex_ptn_parse( pregex_ptn** ptn, pregex_accept* accept, uchar* str, int flags );


int pregex_ref_init( pregex_result** ref, int* ref_count, int ref_all, int flags );
void pregex_ref_update( pregex_result* ref, uchar* strp, psize off );


uchar* pchar_to_uchar( pchar* str, pboolean freestr );
pchar* uchar_to_pchar( uchar* str, pboolean freestr );
uchar* plong_to_uchar( plong l );
pchar* plong_to_pchar( plong l );
uchar* pulong_to_uchar( pulong ul );
pchar* pulong_to_pchar( pulong ul );
uchar* pdouble_to_uchar( pdouble d );
pchar* pdouble_to_pchar( pdouble d );


uchar* pstr_append_char( uchar* str, wchar chr );
uchar* pstr_append_str( uchar* dest, uchar* src, boolean freesrc );
uchar* pstr_append_nchar( uchar* str, uchar* append, psize num );
uchar* pstr_replace( uchar* str, uchar* find, uchar* replace );
uchar* pstrzero( uchar* str );
uchar* psetstr( uchar** str, uchar* val );
char* pgetstr( char* str );
uchar* pstrdup( uchar* str );
uchar* pstrndup( uchar* str, psize len );
psize pstrlen( uchar* str );
int psprintf( uchar* res, uchar* fmt, ... );
int pvasprintf( uchar** str, uchar* fmt, va_list ap );
uchar* pasprintf( uchar* fmt, ... );
long patol( uchar* str );
double patof( uchar* str );
int patoi( uchar* str );
uchar* pstr_render( uchar* tpl, ... );
uchar* pstr_strip( uchar* str );
char* pstr_ltrim( char* s );
char* pstr_rtrim( char* s );
char* pstr_trim( char* s );
int pstr_tok( uchar*** tokens, uchar* str, uchar* sep, int limit );
uchar* pstrupr( uchar* str );
uchar* pstrlwr( uchar* str );
int pstrcasecmp( uchar* s1, uchar* s2 );
int pstrncasecmp( uchar* s1, uchar* s2, pint n );
int pstr_char( wchar* retc, uchar *str, pboolean escapeseq );
#ifdef UNICODE
pchar* Pstrdup( pchar* str );
int Psprintf( pchar* res, pchar* fmt, ... );
int Pvasprintf( pchar** str, pchar* fmt, va_list ap );
pchar* Pasprintf( pchar* fmt, ... );
pchar* Pstr_append_char( pchar* str, wchar chr );
pchar* Pstr_append_str( pchar* dest, pchar* src, boolean freesrc );
pchar* Pstr_append_nchar( pchar* str, pchar* append, psize num );
psize Pstrlen( pchar* str );
#endif


int u8_seqlen(uchar *s);
#ifdef UTF8
wchar u8_char( uchar* str );
#else
wchar u8_char( uchar* str );
#endif
uchar* u8_move( uchar* str, int count );
wchar u8_parse_char( uchar** ch );
int u8_toucs(wchar *dest, int sz, uchar *src, int srcsz);
int u8_toutf8(uchar *dest, int sz, wchar *src, int srcsz);
int u8_wc_toutf8(uchar *dest, wchar ch);
int u8_offset(uchar *str, int charnum);
int u8_charnum(uchar *s, int offset);
int u8_strlen(uchar *s);
wchar u8_nextchar(uchar *s, int *i);
void u8_inc(uchar *s, int *i);
void u8_dec(uchar *s, int *i);
int octal_digit(uchar c);
int hex_digit(uchar c);
int u8_read_escape_sequence(uchar *str, wchar *dest);
int u8_unescape(uchar *buf, int sz, uchar *src);
int u8_escape_wchar(uchar *buf, int sz, wchar ch);
int u8_escape(uchar *buf, int sz, uchar *src, int escape_quotes);
uchar *u8_strchr(uchar *s, wchar ch, int *charn);
uchar *u8_memchr(uchar *s, wchar ch, size_t sz, int *charn);
int u8_is_locale_utf8(uchar *locale);
#if 0
int u8_vprintf(uchar *fmt, va_list ap);
int u8_printf(uchar *fmt, ...);
#endif


pint to_base64( uchar** outstream, uchar* instream, psize size );
pint from_base64( uchar** outstream, psize* outsize, uchar* instream );


uchar* pbasename( uchar* path );
pboolean pfileexists( uchar* filename );
int map_file( char** cont, uchar* filename );
pint pgetopt( uchar* opt, uchar** param, pint* next, pint argc, uchar** argv, uchar* optstr, uchar* loptstr, pint idx );


void pvar_init( pvar* var );
void pvar_reset( pvar* var );


pbyte pvar_get_byte( pvar* var );
uchar pvar_get_char( pvar* var );
pint pvar_get_int( pvar* var );
plong pvar_get_long( pvar* var );
pulong pvar_get_ulong( pvar* var );
pfloat pvar_get_float( pvar* var );
pdouble pvar_get_double( pvar* var );
uchar* pvar_get_cstring( pvar* var );
uchar* pvar_get_string( pvar* var );
pchar* pvar_get_wcstring( pvar* var );
pchar* pvar_get_wstring( pvar* var );


pbyte pvar_set_byte( pvar* var, pbyte b );
uchar pvar_set_char( pvar* var, uchar c );
pint pvar_set_int( pvar* var, pint i );
plong pvar_set_long( pvar* var, plong l );
pulong pvar_set_ulong( pvar* var, pulong ul );
pfloat pvar_set_float( pvar* var, pfloat f );
pdouble pvar_set_double( pvar* var, pdouble d );
uchar* pvar_set_cstring( pvar* var, uchar* s );
uchar* pvar_set_string( pvar* var, uchar* s );
pchar* pvar_set_wcstring( pvar* var, pchar* ws );
pchar* pvar_set_wstring( pvar* var, pchar* ws );


pbyte pvar_to_byte( pvar* var );
uchar pvar_to_char( pvar* var );
pint pvar_to_int( pvar* var );
plong pvar_to_long( pvar* var );
pulong pvar_to_ulong( pvar* var );
pfloat pvar_to_float( pvar* var );
pdouble pvar_to_double( pvar* var );
uchar* pvar_to_string( pvar* var );
pchar* pvar_to_wstring( pvar* var );
pint pvar_convert( pvar* var, pbyte type );


XML_T xml_child( XML_T xml, uchar* name );
XML_T xml_idx( XML_T xml, int idx );
uchar* xml_attr( XML_T xml, uchar* attr );
plong xml_int_attr( XML_T xml, uchar* attr );
pdouble xml_float_attr( XML_T xml, uchar* attr );
XML_T xml_vget( XML_T xml, va_list ap );
XML_T xml_get( XML_T xml, ... );
uchar ** xml_pi( XML_T xml, uchar* target );
uchar* xml_decode( uchar* s, uchar ** ent, uchar t );
uchar* xml_str2utf8( uchar ** s, size_t* len );
void xml_free_attr( uchar ** attr );
XML_T xml_parse_str( uchar* s, size_t len );
XML_T xml_parse_fp( FILE* fp );
XML_T xml_parse_file( uchar* file );
uchar* xml_ampencode( uchar* s, size_t len, uchar ** dst, size_t* dlen, size_t* max, short a );
uchar* xml_toxml( XML_T xml );
void xml_free( XML_T xml );
uchar* xml_error( XML_T xml );
XML_T xml_new( uchar* name );
XML_T xml_insert( XML_T xml, XML_T dest, size_t off );
XML_T xml_add_child( XML_T xml, uchar* name, size_t off );
XML_T xml_set_txt( XML_T xml, uchar* txt );
XML_T xml_set_attr( XML_T xml, uchar* name, uchar* value );
XML_T xml_set_int_attr( XML_T xml, uchar* name, plong value );
XML_T xml_set_float_attr( XML_T xml, uchar* name, pdouble value );
XML_T xml_set_flag( XML_T xml, short flag );
int xml_count( XML_T xml );
int xml_count_all( XML_T xml );
XML_T xml_cut( XML_T xml );


#endif 

