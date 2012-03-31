/*
 * khashs.c
 *
 *  Created on: 26.03.2010
 *      Author: constantin
 */

#include "khashs.h"
#include "kdllist.h"

KHASH msizehash( ksize msize, ksize _size ){
	KHASH hash = 0;
	if( msize < 13 ){
		hash = 0;
	}else if( msize < 25 ){
		hash = 1;
	}else if( msize < 33 ){
		hash = 2;
	}else hash = 3;

	return hash % _size;
};

KHASH jstringhash( const char *string, ksize _size )
{
    KHASH hash = 0;

    ksize len = strlen( string );
    KHASH i;
    for( i = 0; i < len; i++ )
        hash = 31 * hash + string[i];

    return hash % _size;
};

KHASH mstringhash( const kchar *string, ksize _size )
{
    KHASH hash = 0;

    ksize len = strlen( string );
    KHASH i;
    for( i = 0; i < len; i++ )
        hash = hash + string[i];

    return hash % _size;

};

//==============================================================================


khlitem * khlitem_new()
{
	return malloc( sizeof( khlitem ) );

};
void * khlitem_init( void * _hitem, void * _data, void * _key, ksize _key_size )
{
	khlitem * ret = _hitem;
	if( !ret )
		ret = khlitem_new();

	ret->data = _data;
	ret->key_size = _key_size;
	ret->key = malloc( _key_size );
	memcpy( ret->key, _key, _key_size );

	return ret;

};
void * khlitem_cp( void * _hitem )
{
	if(!_hitem)
		return NULL;

	khlitem * ci = (khlitem *)_hitem;
	return khlitem_init( NULL, ci->data, ci->key, ci->key_size );

};
void * khlitem_data( void * _hitem )
{
	if( _hitem )
		return ((khlitem *)_hitem)->data;

	return NULL;

}
void * khlitem_key( void * _hitem )
{
	if ( _hitem )
		return ((khlitem *)_hitem)->key;

	return NULL;

};
void * khlitem_destroy( void * _hitem )
{
	if( !_hitem )
		return NULL;

	free( ((khlitem*)_hitem)->key );

	free(_hitem);

	return _hitem;

}


//==============================================================================


khtable * khtable_new()
{
	return malloc( sizeof( khtable ) );

};
void * khtable_init( void * _htable, kclass * _list_class, KID _size,
		khashfunc _hashfunc, kcmpfunc _keycmpfunc )
{
	if( !_list_class )
		return NULL;

	khtable * ret = _htable;
	if( !ret )
		ret = khtable_new();

	ret->next = NULL;
	ret->list_class = _list_class;
	ret->list_a = malloc( sizeof( void * )*_size );
	int i;
	for(i = 0; i < _size; i++)
	{
		ret->list_a[i] = (((void *(*)(void*,void*,void*,void*,KID))
				CMETHOD(_list_class, constructor))
				( NULL, NULL, NULL, NULL, 0 ));

	}
	ret->size = _size;
	ret->hashfunc = _hashfunc;
	ret->keycmpfunc = _keycmpfunc;

	return ret;

};
void * khtable_cp( void * _htable )
{
	if( !_htable )
		return NULL;

	khtable * cht = _htable;
	return khtable_init( NULL, cht->list_class, cht->size, cht->hashfunc,
			cht->keycmpfunc );

};

void * khtable_next( void * _htable )
{
	if( _htable )
		return ((khtable *)_htable)->next;

	return NULL;

};

static inline void * khtable_findhlitem( khtable * cht, void * _key, ksize _keysize )
{
	if( !cht | !_key )
		return NULL;

	KHASH hash = cht->hashfunc( _key, cht->size );
	void * curlist = cht->list_a[hash];
	kclass * class = cht->list_class;
	kcmpfunc keycmpf = cht->keycmpfunc;

	khlitem * ci = CAS_LIST(class, iter_begin)( curlist );
	while( ci )
	{
		if( !keycmpf( ci->key, _key ) )
			return ci;

		ci = CAS_LIST(class, iterf)( curlist );

	}

	return NULL;

};

void * khtable_ins( void * _htable, void * _data, void * _key, ksize _keysize )
{
	if( !_htable | !_key )
		return NULL;

	khtable * cht = _htable;
	KHASH hash = cht->hashfunc( _key, cht->size );
	khlitem * ci = khlitem_init( NULL, _data, _key, _keysize );
	CAS_LIST(cht->list_class, push)( cht->list_a[hash], ci );

	return ci;

};
void * khtable_get( void * _htable, void * _key, ksize _keysize )
{
	khlitem * ci = khtable_findhlitem( _htable, _key, _keysize );

	if( ci )
		return ci->data;

	return NULL;

};
void * khtable_set( void * _htable, void * _data, void * _key, ksize _keysize )
{
	khlitem * ci = khtable_findhlitem( _htable, _key, _keysize );
	if( ci )
	{
		ci->data = _data;
		return ci;

	}

	return NULL;

};

void * khtable_ins_set( void * _htable, void * _data, void * _key, ksize _keysize )
{
	void * ret = khtable_set( _htable, _data, _key, _keysize );
	if( !ret )
		return khtable_ins( _htable, _data, _key, _keysize );

	return ret;

};

void khtable_rm( void * _htable, void * _key, ksize _keysize )
{
	if( !_htable )
		return;

	khtable * cht = _htable;
	KHASH hash = cht->hashfunc( _key, cht->size );
	void * curlist = cht->list_a[hash];
	kclass * class = cht->list_class;
	kcmpfunc keycmpf = cht->keycmpfunc;

	khlitem * ci = CAS_LIST(class, iter_begin)( curlist );
	while( ci )
	{
		if( !keycmpf( ci->key, _key ) )
			break;

		ci = CAS_LIST(class, iterf)( curlist );

	}

	if( ci )
	{
		KID id = CAS_LIST(class,id)( curlist, ci, ptr_cmp );
		if( id != BADID )
			CAS_LIST(class, rmn)( curlist, id );

		khlitem_destroy( ci );

	}

};

void khtable_destroy( void * _htable )
{
	if( !_htable)
		return;

	khtable * cht = _htable;
	void * curlist;
	kclass * class = cht->list_class;

	KID i;
	for( i = 0; i < cht->size; i++ )
	{
		curlist = cht->list_a[i];
		CAS_LIST(class,iter_res)( curlist );
		while( khlitem_destroy( CAS_LIST(class,iterf)( curlist ) ) ){;};
		CMETHOD(class,destructor)( curlist );

	}
	free( _htable );

};


