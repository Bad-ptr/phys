#ifndef KDLLIST_H_
#define KDLLIST_H_


#include "shared.h"
//#include "klitem.h"
#include "kobject.h"


typedef struct kdlptr_s
{
	void * next;
	void * prev;

} kdlptr;

void * kdlptr_next( void * _dlptr );
void * kdlptr_prev( void * _dlptr );

kbool kdlptr_insa( void * _dlptr, void * _place );
kbool kdlptr_insb( void * _dlptr, void * _place );

KID kdlptr_id( void * _rdlptr, void * _dlptr );
void * kdlptr_byid( void * _rlptr, KID _id );

void * kdlptr_rmn( void * _dlptr );
void * kdlptr_rmp( void * _dlptr );

//==============================================================================

typedef struct kdlitem_s
{
	kdlptr dlptr;
	void * data;

} kdlitem;

typedef kdlitem * (* dlitemfunc)( kdlitem * );
typedef kdlitem * (* dlitemsfunc)( kdlitem *, kdlitem * );
typedef kint (* dlitemscmpfunc)( kdlitem *, kdlitem * );

kdlitem * kdlitem_new();
kdlitem * kdlitem_mk( void * _next, void * _prev, void * _data );
void * kdlitem_init( void * _dlitem, void * _next, void * _prev, void * _data );
void * kdlitem_cp( void * _dlitem );
void * kdlitem_next( void * _dlitem );
void * kdlitem_prev( void * _dlitem );
void * kdlitem_data( void * _dlitem );
kint kdlitem_cmp( void * _fdlitem, void * _sdlitem, kcmpfunc _cmpfunc );
void kdlitem_destroy( void * _dlitem );


//==============================================================================


#define D_LIST_LENGTH 10


typedef struct kdllist_s
{
	kdlitem *head;
	kdlitem *tail;
	kdlitem *citer;

	KID len;

} kdllist;



typedef kdllist * (* dllfunc)( kdllist * );
typedef kdllist * (* dllsortfunc)( kdllist *, dlitemscmpfunc );

void * kdllist_new();
void * kdllist_mk( void * _head, void * _tail, void * _citer, KID _len );
void * kdllist_init( void * _dllist, void * _head, void * _tail,
		void * _citer, KID _len );

void * kdllist_cp( void * _dllist );
void * kdllist_cpr( void * _dllist );

KID kdllist_len( void * _dllist );

void kdllist_iter_res( void * _dllist );
void * kdllist_iter_seek( void * _dllist, KID _id );
void * kdllist_iter_begin( void * _dllist );
void * kdllist_iterf( void * _dllist );
void * kdllist_iterb( void * _dllist );
//kdllist * kdllist_cpir( kdllist * _dllist, kid _len );

void * kdllist_push( void * _dllist, void * _data );
void * kdllist_pop( void * _dllist );
void * kdllist_tpush( void * _dllist, void * _data );
void * kdllist_tpop( void * _dllist );

void * kdllist_rmn( void * _dllist, KID _id );
void * kdllist_rmp( void * _dllist, KID _id );
void kdllist_rmr( void * _dllist );


void * kdllist_insa( void * _dllist, void * _data, KID _id );
void * kdllist_insb( void * _dllist, void * _data, KID _id );

//TODO: implement this
//kbool kllist_map( void * _llist, unaryfunc _mapfunc );
//kbool kllist_reduce( void * _llist, binaryfunc _reducefunc );
//kbool kllist_sort( void * _llist, llsortfunc _sortfunc );

//void * kllist_swap( kllist * _llist, kid _fid, kid _sid );

KID kdllist_id( void * _dllist, void * _data, kcmpfunc _cmpfunc );
void * kdllist_byid( void * _dllist, KID id );
//TODO: implement this
//void * kllist_find( kllist * _llist, void * _tofind, binaryfunc _cmpf );

kbool kdllist_set( void * _dllist, void * _data, KID _id );

void kdllist_destroy( void * _dllist );


//==============================================================================

static klistmethods as_kdllist = {
		kdllist_cpr,
		kdllist_len,

		kdllist_iter_res,
		kdllist_iter_seek,
		kdllist_iter_begin,
		kdllist_iterf,
		kdllist_iterb,

		kdllist_push,
		kdllist_pop,
		kdllist_tpush,
		kdllist_tpop,

		kdllist_insa,
		kdllist_insb,

		kdllist_set,

		kdllist_id,
		kdllist_byid,

		kdllist_rmn,
		kdllist_rmp,
		kdllist_rmr

};
/*
static kmethods kdllist_methods = {
		NULL,
		&as_kdllist,
		kdllist_init,
		kdllist_cp,
		kdllist_destroy,
		NULL,
		NULL,
		NULL,
		NULL,
		NULL

};
*/
static kclass kdllist_class = {
		"kdllist",
		"double linked list class",
		NULL,
		NULL,
		//kdllist_methods,
		{
			NULL,
			&as_kdllist,
			kdllist_init,
			kdllist_cp,
			kdllist_destroy,
			NULL,
			NULL,
			NULL,
			NULL,
			NULL

		},
		sizeof( kdllist )

};

void * dllistobj_init( void * _llist );


#endif
