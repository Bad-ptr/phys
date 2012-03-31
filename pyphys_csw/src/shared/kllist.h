#ifndef KLLIST_H_
#define KLLIST_H_


#include "shared.h"
//#include "klitem.h"
#include "kobject.h"


typedef struct klptr_s
{
	void * next;

} klptr;

void * klptr_next( void * _lptr );
void * klptr_prev( void * _rlptr, void * _lptr );

kbool klptr_insa( void * _lptr, void * _place );
kbool klptr_insb( void * _rlptr, void * _lptr, void * _place );

KID klptr_id( void * _rlptr, void * _lptr );
void * klptr_byid( void * _rlptr, KID _id );

void * klptr_rmn( void * _rlptr, void * _lptr );
void * klptr_rmp( void * _rlptr, void * _lptr );

//==============================================================================

typedef struct klitem_s
{
	klptr lptr;
	void * data;

} klitem;

typedef klitem * (* litemfunc)( klitem * );
typedef klitem * (* litemsfunc)( klitem *, klitem * );
typedef kint (* litemscmpfunc)( klitem *, klitem * );

klitem * klitem_new();
klitem * klitem_mk( void * _next, void * _data );
void * klitem_init( void * _litem, void * _next, void * _data );
void * klitem_cp( void * _litem );
void * klitem_next( void * _litem );
void * klitem_data( void * _litem );
kint klitem_cmp( void * _flitem, void * _slitem, kcmpfunc _cmpfunc );
void * klitem_destroy( void * _litem );


//==============================================================================


#define D_LIST_LENGTH 10


typedef struct kllist_s
{
	klitem * head;
	klitem * tail;
	klitem * citer;

	KID len;

} kllist;



typedef kllist * (* llfunc)( kllist * );
typedef kllist * (* llsortfunc)( kllist *, litemscmpfunc );

kllist * kllist_new();
kllist * kllist_mk( void * _head, void * _tail, void * _citer, KID _len );
void * kllist_init( void * _llist, void * _head, void * _tail,
		void * _citer, KID _len );
#define KLLIST_INIT_NEW kllist_init( NULL, NULL, NULL, NULL, 0 )

void * kllist_cp( void * _llist );
void * kllist_cpr( void * _llist );

KID kllist_len( void * _llist );

void kllist_iter_res( void * _llist );
void * kllist_iter_seek( void * _llist, KID _id );
void * kllist_iter_begin( void * _llist );
void * kllist_iterf( void * _llist );
void * kllist_iterb( void * _llist );
//kllist * kllist_cpir( kllist * _llist, kid _len );

void * kllist_push( void * _llist, void * _data );
void * kllist_pop( void * _llist );
void * kllist_tpush( void * _llist, void * _data );
void * kllist_tpop( void * _llist );

void * kllist_rmn( void * _llist, KID _id );
void * kllist_rmp( void * _llist, KID _id );
void kllist_rmr( void * _llist );


void * kllist_insa( void * _llist, void * _data, KID _id );
void * kllist_insb( void * _llist, void * _data, KID _id );

//TODO: implement this
//kbool kllist_map( void * _llist, unaryfunc _mapfunc );
//kbool kllist_reduce( void * _llist, binaryfunc _reducefunc );
//kbool kllist_sort( void * _llist, llsortfunc _sortfunc );

//void * kllist_swap( kllist * _llist, kid _fid, kid _sid );

KID kllist_id( void * _llist, void * _data, kcmpfunc _cmpfunc );
void * kllist_byid( void * _llist, KID id );
//TODO: implement this
//void * kllist_find( kllist * _llist, void * _tofind, binaryfunc _cmpf );

kbool kllist_set( void * _llist, void * _data, KID _id );

void kllist_destroy( void * _llist );


//==============================================================================

static klistmethods as_kllist = {
		kllist_cpr,
		kllist_len,

		kllist_iter_res,
		kllist_iter_seek,
		kllist_iter_begin,
		kllist_iterf,
		kllist_iterb,

		kllist_push,
		kllist_pop,
		kllist_tpush,
		kllist_tpop,

		kllist_insa,
		kllist_insb,

		kllist_set,

		kllist_id,
		kllist_byid,

		kllist_rmn,
		kllist_rmp,
		kllist_rmr

};
/*
static kmethods kllist_methods = {
		NULL,
		&as_kllist,
		kllist_init,
		kllist_cp,
		kllist_destroy,
		NULL,
		NULL,
		NULL,
		NULL,
		NULL

};
*/
static kclass kllist_class = {
		"kllist",
		"linked list class",
		NULL,
		NULL,
		//kllist_methods,
		{
			NULL,
			&as_kllist,
			kllist_init,
			kllist_cp,
			kllist_destroy,
			NULL,
			NULL,
			NULL,
			NULL,
			NULL

		},
		sizeof( kllist )

};

void * llistobj_init( void * _llist );



#endif
