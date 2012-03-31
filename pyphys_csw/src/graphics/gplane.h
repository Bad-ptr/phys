#ifndef K_GPLANE_H
#define K_GPLANE_H


#include "gshared.h"

#include "gvertex.h"


typedef struct kgplane_s{

	kgvert p;
	kgvert n;

} kgplane;

void Draw ( kgplane * gplane );

#endif

