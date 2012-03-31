#ifndef K_GVERTEX_H
#define K_GVERTEX_H

//#define POS 0
//#define TC 1
//#define RGB 2
//#define ALPH 3

#include "gshared.h"
#include "../math/kmquat.h"


typedef struct kgvert_s
{

	kmvect3f pos;
    kmquat4f q;

	kgtexcoords tcoords;

	kgcolor color;

} kgvert;

void Draw( kgvert * vert );

#endif

