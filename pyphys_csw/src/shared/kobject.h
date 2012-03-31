/*
 * kobject.h
 *
 *  Created on: 27.03.2010
 *      Author: constantin
 */

#ifndef KOBJECT_H_
#define KOBJECT_H_


#include "shared.h"


typedef struct knummethods_s
{
	kunfunc neg;
	kunfunc abs;

	kbinfunc add;
	kbinfunc sub;
	kbinfunc mul;
	kbinfunc div;

	kterfunc pow;
	kbinfunc rem;

	kbinfunc lshift;
	kbinfunc rshift;
	kbinfunc and;
	kbinfunc or;
	kbinfunc xor;
	kunfunc inv;

	kbinfunc iadd;
	kbinfunc isub;
	kbinfunc imul;
	kbinfunc idiv;

	kterfunc ipow;
	kbinfunc irem;

	kbinfunc ilshift;
	kbinfunc irshift;
	kbinfunc iand;
	kbinfunc ixor;
	kbinfunc ior;

} knummethods;


typedef struct klistmethods_s
{
	kunfunc cpr;
	KID (* len)( void *);

	void (* iter_res)( void * _list );
	void * (* iter_seek)( void * _list, KID _id );
	kunfunc iter_begin;
	kunfunc iterf;
	kunfunc iterb;

	kbinfunc push;
	kunfunc pop;

	kbinfunc tpush;
	kunfunc tpop;

	void * (* insa)( void * _list, void * _data, KID _id );
	void * (* insb)( void * _list, void * _data, KID _id );

	kbool (* set)( void * _list, void * _data, KID _id );

	KID (* id)( void * _list, void * _data, kcmpfunc _cmpfunc );
	void * (* byid)( void * _list, KID _id );

	void * (* rmn)( void * _list, KID _id );
	void * (* rmp)( void * _list, KID _id );
	void (* rmr)( void * _list );

//	void   (* destroy)( void * _list );

} klistmethods;

typedef struct kmethods_s
{
	knummethods *as_num;
	klistmethods *as_list;

	void * constructor;
	kunfunc cp;
	void (* destructor)(void *);

	khashfunc hashfunc;
	kbinfunc str;
	kbinfunc call;
	kcmpfunc cmp;

	void * self;

}kmethods;

struct kclass_s;

#define OBJ_HEAD	\
	ksize refcnt;	\
	struct kclass_s * class

typedef struct kobject_s
{
	OBJ_HEAD;

} kobject;


typedef struct kclass_s
{
	//OBJ_HEAD;
	char * name;
	char * doc;
	struct kclass_s * superclass;

	struct megashit * members;
	kmethods methods;
	ksize size;

} kclass;


//==============================================================================

#define METHOD(OBJ,METHOD) ((kobject*)OBJ)->class->methods.METHOD
#define CMETHOD(CLASS,METHOD) ((kclass*)CLASS)->methods.METHOD

#define IS_LIST(OBJ) NULL != ((kobject*)OBJ)->class->methods.as_list
#define CIS_LIST(CLASS) NULL != ((kclass*)CLASS)->methods.as_list

#define CAS_LIST(CLASS,METHOD) CMETHOD(CLASS,as_list->METHOD)
#define AS_LIST(OBJ,METHOD) METHOD(OBJ,as_list->METHOD)

//==============================================================================

#define GEN_BTYPE_OBJ_S(TYPE)	\
	typedef struct TYPE##_s{	\
		OBJ_HEAD;				\
		TYPE



#endif /* KOBJECT_H_ */
