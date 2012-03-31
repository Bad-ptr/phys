
#include "kllist.h"
#include "kmmngr.h"


INLINE void * klptr_next( void * _lptr )
{
	if ( !_lptr )
		return NULL;

	return ((klptr *)_lptr)->next;

};
void * klptr_prev( void * _rlptr, void * _lptr )
{
	if( !_rlptr | !_lptr )
		return NULL;
	if( _rlptr == _lptr )
		return NULL;

	klptr * rlptr = (klptr *)_rlptr;

	for(; rlptr; rlptr = (klptr *)rlptr->next )
		if( rlptr->next == _lptr )
			return rlptr;

	return NULL;

};

INLINE kbool klptr_insa( void * _lptr, void * _place )
{
	if ( !_place || !_lptr )
		return kfalse;

	klptr * lptr=(klptr *)_lptr;
	klptr * place=(klptr *)_place;
	lptr->next = place->next;
	place->next = _lptr;

	return ktrue;

};
INLINE kbool klptr_insb( void * _rlptr, void * _lptr, void * _place )
{
	if ( !_place || !_lptr )
		return kfalse;

	klptr * lptr = (klptr *)_lptr;
	klptr * prev = (klptr *)klptr_prev( _rlptr, _place );

	if( prev )
		prev->next = _lptr;
	lptr->next = _place;

	return ktrue;

};


KID klptr_id( void * _rlptr, void * _lptr )
{
	if( !_rlptr | !_lptr )
		return BADID;

	void * rlptr = _rlptr;

	KID id;
	for( id = 0; rlptr; id++ )
	{
		if( rlptr == _lptr )
			return id;

		rlptr = ((klptr *)rlptr)->next;

	}

	return BADID;

};
void * klptr_byid( void * _rlptr, KID _id )
{
//TODO: do something if _id < 0

	void * rlptr = _rlptr;
	KID id;
	for( id = 0; id < _id; id++ )
	{
		if( !rlptr )
			return NULL;

		rlptr = ((klptr *) rlptr)->next;

	}

	return rlptr;

};

INLINE void * klptr_rmn( void * _rlptr, void * _lptr )
{
	klptr * prev = (klptr *)klptr_prev( _rlptr, _lptr );
	if ( prev )
	{
		prev->next = ((klptr *)_lptr)->next;
		return prev->next;

	}

	return klptr_next( _lptr );

};
INLINE void * klptr_rmp( void * _rlptr, void * _lptr )
{
	klptr * prev = (klptr *)klptr_prev( _rlptr, _lptr );
	if ( prev )
		prev->next = ((klptr *)_lptr)->next;

	return prev;

};

//==============================================================================

INLINE klitem * klitem_new()
{

	return malloc( sizeof( klitem ) );
}
INLINE klitem * klitem_mk( void * _next, void * _data )
{
	klitem * ret = klitem_new();
	ret->lptr.next = _next;
	ret->data = _data;
	return ret;

};
INLINE void * klitem_init( void * _litem, void * _next, void * _data )
{
	klitem * citem = (klitem *)_litem;
	if( !citem )
		return (void *)klitem_mk( _next, _data );
	citem->data = _data;
	citem->lptr.next = _next;

	return citem;

};
INLINE void * klitem_cp( void * _litem )
{
	return (void *)klitem_mk( ((klptr *)_litem)->next, ((klitem *)_litem)->data );

};
INLINE void * klitem_next( void * _litem )
{
	return klptr_next( _litem );

};
INLINE void * klitem_data( void * _litem )
{
	if( _litem )
		return ((klitem *)_litem)->data;

	return NULL;

};
INLINE kint klitem_cmp( void * _flitem, void * _slitem, kcmpfunc _cmpfunc )
{
	return _cmpfunc( ((klitem *)_flitem)->data, ((klitem *)_slitem)->data );

};
INLINE void * klitem_destroy( void * _litem )
{
	if( !_litem )
		return NULL;

	free(_litem);

	return _litem;

};


//==============================================================================

INLINE kllist * kllist_new()
{
	return malloc( sizeof( kllist ) );

};
INLINE kllist * kllist_mk( void * _head, void * _tail, void * _citer, KID _len )
{
	kllist * ret = kllist_new();
	if( !ret )
		return NULL;

	ret->head = _head;
	ret->tail = _tail;
	ret->citer = _citer;
	ret->len = _len;

	return ret;
};
INLINE void * kllist_init( void * _llist, void * _head, void * _tail,
		void * _citer, KID _len )
{
	if( !_llist )
		return kllist_mk( _head, _tail, _citer, _len );

	kllist * ret = (kllist *)_llist;

	ret->head = _head;
	ret->tail = _tail;
	ret->citer = _citer;
	ret->len = _len;

	return _llist;

};

INLINE void * kllist_cp( void * _llist )
{
	if( !_llist )
		return NULL;

	kllist * l = (kllist *)_llist;
	kllist * ret = kllist_mk( l->head, l->tail, l->citer, l->len );
	return ret;

};
void * kllist_cpr( void * _llist )
{
	kllist * ret = kllist_new();
	if( !ret )
		return NULL;

	void * citem = kllist_iter_begin( _llist );
	while( citem )
	{
		kllist_tpush( ret, citem );
		citem = kllist_iterf( _llist );
	}
	return ret;

};

INLINE KID kllist_len( void * _llist )
{
	if( !_llist )
		return BADID;

	return ((kllist *)_llist)->len;

};

INLINE void kllist_iter_res( void * _llist )
{
	if( _llist )
		((kllist *)_llist)->citer = ((kllist *)_llist)->head;

};
INLINE void * kllist_iter_seek( void * _llist, KID _id )
{
	kllist * list = (kllist *)_llist;
	list->citer = klptr_byid( list->head, _id );
	return list->citer;

};
INLINE void * kllist_iter_begin( void * _llist )
{
	kllist_iter_res( _llist );
	return kllist_iterf( _llist );

};
INLINE void * kllist_iterf( void * _llist )
{
	if( !_llist )
		return NULL;

	kllist * list = (kllist *)_llist;
	void * ret = klitem_data( list->citer );
	list->citer = klptr_next( list->citer );
	return ret;

};
INLINE void * kllist_iterb( void * _llist )
{
	if( !_llist )
		return NULL;

	kllist * list = (kllist *)_llist;
	void * ret = klitem_data( list->citer );
	list->citer = klptr_prev( list->head, list->citer );
	return ret;

};

INLINE void * kllist_push( void * _llist, void * _data )
{
	if( !_llist )
		return NULL;

	kllist * list = _llist;
	list->head = (klitem *)klitem_mk( list->head, _data );

	if( 0 == list->len )
		list->tail = list->head;

	list->len += 1;
	return list->head;

};
INLINE void * kllist_pop( void * _llist )
{
	if( !_llist)
		return NULL;

	kllist * list = _llist;

	if( 0 >= list->len )
		return NULL;

	void * ret = klitem_data( list->head );
	klitem * itd = list->head;
	list->head = klptr_next(list->head);
	klitem_destroy( itd );
	list->len -= 1;
	return ret;

};
INLINE void * kllist_tpush( void * _llist, void * _data )
{
	if( !_llist )
		return NULL;

	kllist * list = _llist;
	void * nitem = klitem_mk( NULL, _data);
	if( 0 == list->len )
		return list->head = list->tail = nitem;

	list->tail->lptr.next = nitem;
	list->tail = list->tail->lptr.next;
	list->len += 1;
	return list->tail;

};
INLINE void * kllist_tpop( void * _llist )
{
	if( !_llist)
		return NULL;

	kllist * list = _llist;

	if( 0 >= list->len )
		return NULL;

	void * ret = klitem_data( list->tail );
	klitem * itd = list->tail;
	list->tail = klptr_prev(list->head, list->tail);
	klitem_destroy( itd );
	list->len -= 1;

	return ret;

};

INLINE void * kllist_rmn( void * _llist, KID _id )
{
	if( !_llist )
		return NULL;

	kllist * list = _llist;

	if( 0 >= list->len )
		return NULL;

	klitem * item = klptr_byid( list->head, _id-1 );

	void * item_to_destroy = item->lptr.next;
	void * ret = klptr_next(item_to_destroy);

	klitem_destroy( item_to_destroy );
	item->lptr.next = ret;
	list->len -= 1;
	return ret;

};
INLINE void * kllist_rmp( void * _llist, KID _id )
{
	if( !_llist )
		return NULL;

	kllist * list = _llist;

	if( 0 >= list->len )
		return NULL;

	klitem * item = klptr_byid( list->head, _id-1 );
	void * tmp = klptr_next(item->lptr.next);

	klitem_destroy( item->lptr.next );
	item->lptr.next = tmp;
	list->len -= 1;
	return item;

};
INLINE void kllist_rmr( void * _llist )
{
	kllist * list = (kllist*)_llist;
	for(;list->len > 0;)
		kllist_pop( list );

};


INLINE void * kllist_insa( void * _llist, void * _data, KID _id )
{
	kllist * list = (kllist *)_llist;
	klitem * place = klptr_byid( list->head, _id );
	if( !place )
		return NULL;

	klitem * ni = klitem_mk( place->lptr.next, _data );
	list->len += 1;
	klptr_insa( ni, place );

	return ni;

};
INLINE void * kllist_insb( void * _llist, void * _data, KID _id )
{
	return kllist_insa( _llist, _data, _id-1 );

};

INLINE KID kllist_id( void * _llist, void * _data, kcmpfunc _cmpfunc )
{
	kllist * list = _llist;
	KID id = 0;
	void * cd = kllist_iter_begin( list );
	while( cd )
	{
		if( !_cmpfunc( cd, _data ) )
			return id;

		cd = kllist_iterf( list );
		++id;

	}

	return BADID;

};

INLINE void * kllist_byid( void * _llist, KID id )
{
	klitem * item = klptr_byid( ((kllist *)_llist)->head, id );
	return klitem_data( item );

};

INLINE kbool kllist_set( void * _llist, void * _data, KID _id )
{
	klitem * item = klptr_byid( ((kllist *)_llist)->head, _id );
	if( item )
	{
		item->data = _data;
		return ktrue;

	}

	return kfalse;

};

INLINE void kllist_destroy( void * _llist )
{
	kllist_rmr( _llist );
	free( _llist );

};



//==============================================================================

/*INLINE void * llistobj_init( void * _llist )
{
	if ( !_llist )
		_llist = kllist_init( NULL, NULL, NULL, NULL, 0 );

	return klistobj_init( NULL, _llist, sizeof( kllist ), &kllist_methods );

};*/



