#ifndef	K_SHARED_H
#define	K_SHARED_H

#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <stdio.h>
#include <time.h>

#include "kbtypes.h"

//coord indexes
#define	X 0
#define	Y 1
#define	Z 2
#define	W 3
#define Q 4
//2d texture coords
#define U	0
#define V	1
//plane
#define	P	0
#define	N	1
// angle indexes
#define	PITCH	0 // up / down
#define	YAW		1 // left / right
#define	ROLL	2 // fall over


#define	NZEROF	0.000001f
#define	ZEROF	0.0f
#define	ONEF	1.0f

#define BADID INT_MIN


#define INLINE inline
#define INLINEX extern inline


void * kzmalloc( ksize _ksize );



#endif

