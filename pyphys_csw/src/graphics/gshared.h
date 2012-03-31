#ifndef K_GSHARED_H
#define K_GSHARED_H

#include "../shared/shared.h"


typedef union kgtexcoords_u
{
	struct{
	kfloat u, v, w;
	}uvw;
	struct{
	kfloat s, t, q;
	}stq;

} kgtexcoords;


typedef struct kgcolor_s
{

    kfloat r,g,b,a;

} kgcolor;


#endif

