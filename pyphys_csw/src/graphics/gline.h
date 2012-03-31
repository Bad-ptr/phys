#ifndef K_GLINE_H
#define K_GLINE_H


#include "gshared.h"

#include "gvertex.h"

typedef struct kgline_s{

	kgvert b;
	kgvert e;

} kgline;

void Draw( kgline * gline );

#endif
