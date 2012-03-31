
#include "kdllist.h"
#include "kmmngr.h"

INLINE void * kdlptr_next( void * _dlptr )
{
	if ( !_dlptr )
		return NULL;

	return ((kdlptr *)_dlptr)->next;

};
void * kdlptr_prev( void * _dlptr )
{
	if( !_dlptr )
		return NULL;

	return ((kdlptr *)_dlptr)->prev;

};

INLINE kbool kdlptr_insa( void * _dlptr, void * _place )
{
	if ( !_place || !_dlptr )
		return kfalse;

	kdlptr * dlptr=(kdlptr *)_dlptr;
	kdlptr * place=(kdlptr *)_place;
	dlptr->next = place->next;
	dlptr->prev = _place;
	place->next = _dlptr;

	if( dlptr->next )
		((kdlptr *)dlptr->next)->prev = _dlptr;

	return ktrue;

};
INLINE kbool kdlptr_insb( void * _dlptr, void * _place )
{
	if ( !_place || !_dlptr )
		return kfalse;

	kdlptr * dlptr = (kdlptr *)_dlptr;

	dlptr->prev = ((kdlptr *)_place)->prev;
	dlptr->next = _place;

	((kdlptr *)_place)->prev = _dlptr;

	if( dlptr->prev )
		((kdlptr *)dlptr->prev)->next = _dlptr;


	return ktrue;

};


KID kdlptr_id( void * _rdlptr, void * _dlptr )
{
	if( !_rdlptr | !_dlptr )
		return BADID;

	void * rdlptr = _rdlptr;

	KID id;
	for( id = 0; rdlptr; id++ )
	{
		if( rdlptr == _dlptr )
			return id;

		rdlptr = ((kdlptr *)rdlptr)->next;

	}

///* XXX do we need this ?
	//try to search backward...
	rdlptr = _rdlptr;

	for( id = 0; rdlptr; id-- )
	{
		if( rdlptr == _dlptr )
			return id;

		rdlptr = ((kdlptr *)rdlptr)->prev;

	}
//*/

	return BADID;

};
void * kdlptr_byid( void * _rdlptr, KID _id )
{
	void * rdlptr = _rdlptr;
	KID id;

	if( _id > 0 )
	{
		for( id = 0; id < _id; id++ )
		{
			if( !rdlptr )
				return NULL;

			rdlptr = ((kdlptr *)rdlptr)->next;

		}

	}else
	{
		for( id = 0; id > _id; id-- )
		{
			if( !rdlptr )
				return NULL;

			rdlptr = ((kdlptr *)rdlptr)->prev;

		}

	}

	return rdlptr;

};

INLINE void * kdlptr_rmn( void * _dlptr )
{
	kdlptr * prev = (kdlptr *)kdlptr_prev( _dlptr );
	if ( prev )
		prev->next = ((kdlptr *)_dlptr)->next;

	kdlptr * next = (kdlptr *)kdlptr_next( _dlptr );
	if ( next )
		next->prev = prev;

	return next;

};
INLINE void * kdlptr_rmp( void * _dlptr )
{
	kdlptr * prev = (kdlptr *)kdlptr_prev( _dlptr );
	if ( prev )
		prev->next = ((kdlptr *)_dlptr)->next;

	kdlptr * next = (kdlptr *)kdlptr_next( _dlptr );
	if ( next )
		next->prev = prev;

	return prev;

};

//==============================================================================

INLINE kdlitem * kdlitem_new()
{

	return malloc( sizeof( kdlitem ) );
}
INLINE kdlitem * kdlitem_mk( void * _next, void * _prev, void * _data )
{
	kdlitem * ret = kdlitem_new();
	ret->dlptr.next = _next;
	ret->dlptr.prev = _prev;
	ret->data = _data;
	return ret;

};
INLINE void * kdlitem_init( void * _dlitem,
		void * _next, void * _prev, void * _data )
{
	kdlitem * citem = (kdlitem *)_dlitem;
	if( !citem )
		return (void *)kdlitem_mk( _next, _prev, _data );

	citem->data = _data;
	citem->dlptr.next = _next;
	citem->dlptr.prev = _prev;

	return citem;

};
INLINE void * kdlitem_cp( void * _dlitem )
{
	kdlitem * citem = (kdlitem *)_dlitem;
	return (void *)kdlitem_mk( citem->dlptr.next, citem->dlptr.prev, citem->data );

};
INLINE void * kdlitem_next( void * _dlitem )
{
	return kdlptr_next( _dlitem );

};
INLINE void * kdlitem_prev( void * _dlitem )
{
	return kdlptr_prev( _dlitem );

};
INLINE void * kdlitem_data( void * _dlitem )
{
	if( _dlitem )
		return ((kdlitem *)_dlitem)->data;

	return NULL;

};
INLINE kint kdlitem_cmp( void * _fdlitem, void * _sdlitem, kcmpfunc _cmpfunc )
{
	return _cmpfunc( ((kdlitem *)_fdlitem)->data, ((kdlitem *)_sdlitem)->data );

};
INLINE void kdlitem_destroy( void * _dlitem )
{
	free( _dlitem );

};


//==============================================================================

INLINE void * kdllist_new()
{
	return malloc( sizeof( kdllist ) );

}
INLINE void * kdllist_mk( void * _head, void * _tail, void * _citer, KID _len )
{
	kdllist * ret = kdllist_new();
	ret->head = _head;
	ret->tail = _tail;
	ret->citer = _citer;
	ret->len = _len;

	return ret;
};
INLINE void * kdllist_init( void * _dllist, void * _head, void * _tail,
		void * _citer, KID _len )
{
	if( !_dllist )
		return kdllist_mk( _head, _tail, _citer, _len );

	kdllist * ret = (kdllist *)_dllist;

	ret->head = _head;
	ret->tail = _tail;
	ret->citer = _citer;
	ret->len = _len;

	return _dllist;

};

INLINE void * kdllist_cp( void * _dllist )
{
	if( !_dllist )
		return NULL;

	kdllist * l = (kdllist *)_dllist;
	return kdllist_mk( l->head, l->tail, l->citer, l->len );;

};

INLINE void * kdllist_cpr( void * _dllist )
{
	kdllist * ret = kdllist_new();
	void * citem = kdllist_iter_begin( _dllist );
	ret->tail = ret->head = kdlitem_mk( NULL, NULL, citem );
	citem = kdllist_iterf( citem );
	while( citem )
	{
		kdllist_tpush( _dllist, citem );
		citem = kdllist_iterf( _dllist );
	}
	return ret;

};
INLINE KID kdllist_len( void * _dllist )
{
	if( !_dllist )
		return BADID;

	return ((kdllist *)_dllist)->len;

};
INLINE void kdllist_iter_res( void * _dllist )
{
	if( _dllist )
		((kdllist *)_dllist)->citer = ((kdllist *)_dllist)->head;

};
INLINE void * kdllist_iter_seek( void * _dllist, KID _id )
{
	kdllist * dlist = (kdllist *)_dllist;
	dlist->citer = kdlptr_byid( dlist->head, _id );
	return dlist->citer;

};
INLINE void * kdllist_iter_begin( void * _dllist )
{
	kdllist_iter_res( _dllist );
	return kdllist_iterf( _dllist );

};
INLINE void * kdllist_iterf( void * _dllist )
{
	if( !_dllist )
		return NULL;

	kdllist * dlist = (kdllist *)_dllist;
	void * ret = kdlitem_data( dlist->citer );
	dlist->citer = kdlptr_next( dlist->citer );
	return ret;

};
INLINE void * kdllist_iterb( void * _dllist )
{
	if( !_dllist )
		return NULL;

	kdllist * dlist = (kdllist *)_dllist;
	void * ret = kdlitem_data( dlist->citer );
	dlist->citer = kdlptr_prev( dlist->citer );
	return ret;

};

INLINE void * kdllist_push( void * _dllist, void * _data )
{
	if( !_dllist )
		return NULL;

	kdllist * dlist = _dllist;

	void * prev=NULL;
	if(dlist->head)
		prev=dlist->head->dlptr.prev;

	dlist->head = kdlitem_mk(dlist->head, prev, _data );

	if( 0 == dlist->len )
		dlist->tail = dlist->head;

	dlist->len += 1;
	return dlist->head;

};
INLINE void * kdllist_pop( void * _dllist )
{
	if( !_dllist)
		return NULL;

	kdllist * dlist = _dllist;

	if( 0 >= dlist->len )
		return NULL;

	void * ret = kdlitem_data( dlist->head );
	kdlitem * itd = dlist->head;
	dlist->head = kdlptr_rmn(dlist->head);
	kdlitem_destroy( itd );
	dlist->len -= 1;
	return ret;

};
INLINE void * kdllist_tpush( void * _dllist, void * _data )
{
	if( !_dllist )
		return NULL;

	kdllist * dlist = _dllist;
	void * nitem = (kdlitem *)kdlitem_mk(
			kdlptr_next(dlist->tail), dlist->tail, _data);

	if( 0 == dlist->len )
		return dlist->head = dlist->tail = nitem;

	dlist->tail->dlptr.next = nitem;
	dlist->tail = (kdlitem *)dlist->tail->dlptr.next;
	dlist->len += 1;
	return dlist->tail;

};
INLINE void * kdllist_tpop( void * _dllist )
{
	if( !_dllist)
		return NULL;

	kdllist * dlist = _dllist;

	if( 0 >= dlist->len )
		return NULL;

	void * ret = kdlitem_data( dlist->tail );
	kdlitem * itd = dlist->tail;
	dlist->tail = (kdlitem *)kdlptr_rmp( itd );
	kdlitem_destroy( itd );
	dlist->len -= 1;

	return ret;

};

INLINE void * kdllist_rmn( void * _dllist, KID _id )
{
	if( !_dllist )
		return NULL;

	kdllist * dlist = _dllist;

	if( 0 >= dlist->len )
		return NULL;

	kdlitem * citem = kdlptr_byid( dlist->head, _id );

	void * ret = kdlptr_rmn( citem );

	kdlitem_destroy( citem );
	dlist->len -= 1;
	return ret;

};
INLINE void * kdllist_rmp( void * _dllist, KID _id )
{
	if( !_dllist )
		return NULL;

	kdllist * dlist = _dllist;

	if( 0 >= dlist->len )
		return NULL;

	kdlitem * citem = kdlptr_byid( dlist->head, _id );

	void * ret = kdlptr_rmp( citem );

	kdlitem_destroy( citem );
	dlist->len -= 1;
	return ret;

};
INLINE void kdllist_rmr( void * _dllist )
{
	kdllist * dlist = (kdllist*)_dllist;
	for(;dlist->len > 0;)
		kdllist_pop( dlist );

};


INLINE void * kdllist_insa( void * _dllist, void * _data, KID _id )
{
	kdllist * dlist = (kdllist *)_dllist;
	kdlitem * place = kdlptr_byid( dlist->head, _id );
	if( !place )
		return NULL;

	kdlitem * ni = kdlitem_mk( place->dlptr.prev, place, _data );
	dlist->len += 1;
	return (kdlitem *)kdlptr_insa( ni, place );

};
INLINE void * kdllist_insb( void * _dllist, void * _data, KID _id )
{
	return kdllist_insa( _dllist, _data, _id-1 );

};

INLINE KID kdllist_id( void * _dllist, void * _data, kcmpfunc _cmpfunc )
{
	kdllist * dlist = _dllist;
	KID id = 0;
	void * cd = kdllist_iter_begin( dlist );
	while( cd )
	{
		if( !_cmpfunc( cd, _data ) )
			return id;

		cd = kdllist_iterf( dlist );
		++id;

	}

	return BADID;

};

INLINE void * kdllist_byid( void * _dllist, KID id )
{
	kdlitem * citem = kdlptr_byid( ((kdllist *)_dllist)->head, id );
	return kdlitem_data( citem );

};

INLINE kbool kdllist_set( void * _dllist, void * _data, KID _id )
{
	kdlitem * citem = kdlptr_byid( ((kdllist *)_dllist)->head, _id );
	if( citem )
	{
		citem->data = _data;
		return ktrue;

	}

	return kfalse;

};

INLINE void kdllist_destroy( void * _dllist )
{
	kdllist_rmr( _dllist );
	free( _dllist );

};

//==============================================================================

/*INLINE void * dllistobj_init( void * _dllist )
{
	if( !_dllist )
		_dllist = kdllist_init( NULL, NULL, NULL, NULL, 0 );

	return klistobj_init( NULL, _dllist, sizeof( kdllist ), &kdllist_methods );

};*/

