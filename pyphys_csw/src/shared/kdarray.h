#ifndef KDARRAY_H_
#define KDARRAY_H_


#include "shared.h"
//#include "klitem.h"
#include "kobject.h"


typedef struct kdarray_s
{
	kptr * data;
	KID len;
	ksize esize;
	KID citer;

} kdarray;


static inline void * kdarray_new()
{
	return malloc( sizeof(kdarray) );

};

static inline void * kdarray_init( kptr _darray, kptr _data, KID _len, ksize _esize )
{
	kdarray * ret = _darray;
	if( !ret )
		ret = kdarray_new();
	if( !ret )
		return NULL;

	ret->data = _data;
	ret->len = _len;
	ret->esize = _esize;
	ret->citer = 0;

	return ret;

};

static inline void * kdarray_cp( kptr _darray )
{
	if( !_darray )
		return NULL;

	kdarray * kda = _darray;

	return kdarray_init( NULL, kda->data, kda->len, kda->esize );

};

static inline void * kdarray_cpr( kptr _darray )
{
	if( !_darray )
		return NULL;
	kdarray * kda = _darray;

	ksize dsize = kda->len * kda->esize;
	kptr * newdata = malloc( dsize );
	memcpy( newdata, kda->data, dsize );

	return kdarray_init( NULL, newdata, kda->len, kda->esize );

};

static inline KID kdarray_len( kptr _darray )
{
	if( !_darray )
		return BADID;

	return ((kdarray *)_darray)->len;

};

static inline void * kdarray_byid( kptr _darray, KID _id )
{
	if( _darray )
		return NULL;

//TODO: do something if _id < 0
	return &(((kdarray *)_darray)->data[_id]);

};

static inline void kdarray_iter_res( kptr _darray )
{
	if( !_darray )
		return;

	kdarray * kda = _darray;
	kda->citer = 0;

};

static inline void * kdarray_iter_seek( kptr _darray, KID _id )
{
	if( !_darray )
		return NULL;

	kdarray * kda = _darray;
	kda->citer = _id;

	return kda->data[kda->citer];

};

static inline kptr kdarray_iter_begin( kptr _darray )
{
	if( !_darray )
		return NULL;

	kdarray * kda = _darray;

	kda->citer = 1;

	return kda->data;

};


//==============================================================================
/*
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

static kclass kdllist_class = {
		"kdllist",
		"double linked list class",
		NULL,
		NULL,
		kdllist_methods,
		sizeof( kdllist )

};

void * dllistobj_init( void * _llist );
*/

#endif
