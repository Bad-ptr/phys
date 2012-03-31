/*
 * khashs.h
 *
 *  Created on: 26.03.2010
 *      Author: constantin
 */

#ifndef KHASHS_H_
#define KHASHS_H_

#include "shared.h"
#include "kobject.h"


#define CHASHF(F) (khashfunc)F

KHASH msizehash( ksize msize, ksize _size );
KHASH jstringhash( const kchar *string, ksize _size );
KHASH mstringhash( const kchar *string, ksize _size );


//==============================================================================

typedef struct khlitem_s
{
	void * data;
	void * key;
	ksize key_size;

} khlitem;


khlitem * khlitem_new();
void * khlitem_init( void * _hitem, void * _data, void * _key, ksize _key_size );
void * khlitem_cp( void * _hitem );
void * khlitem_data( void * _hitem );
void * khlitem_key( void * _hitem );
//TODO: implement this
//kint khlitem_cmp( void * _fhitem, void * _shitem, kcmpfunc _cmpfunc );
//kint khlitem_kcmp( void * _fhitem, void * _shitem, kcmpfunc _cmpfunc );
void * khlitem_destroy( void * _hitem );

//==============================================================================

typedef struct khnode_s
{
	void * next;
	void * items;
	KID level;

} khnode;



//==============================================================================

typedef struct khtable_s
{
	void * next;
	void ** list_a;
	kclass * list_class;
	KID size;

	khashfunc hashfunc;
	kcmpfunc keycmpfunc;

} khtable;

khtable * khtable_new();
void * khtable_init( void * _htable, kclass * _list_class, KID _size,
		khashfunc _hashfunc, kcmpfunc keycmpfunc );
void * khtable_cp( void * _htable );

void * khtable_next( void * _htable );

void * khtable_get( void * _htable, void * _key, ksize _keysize );
void * khtable_ins_set( void * _htable, void * _data, void * _key, ksize _keysize );
void khtable_rm( void * _htable, void * _key, ksize _keysize );

void khtable_destroy( void * _htable );


#endif /* KHASHS_H_ */
