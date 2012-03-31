#ifndef K_MATH_H
#define K_MATH_H


#include "../shared/shared.h"
//#include "kmvector.h"
//#include "kmquat.h"

#ifndef M_PI
#define M_PI		3.14159265358979323846	// matches value in gcc v2 math.h
#define MATH_PI 		(3.14159265359f)
#endif
#define MATH_EPSILON 		(1e-6f)

kfloat deg2rad ( kfloat _deg );

kfloat rad2deg ( kfloat _rad );

// as ID sowtware teached us ;)
// microsoft's fabs seems to be ungodly slow...
//static inline
kfloat kfabs( kfloat f );

//typedef kvert kmvert;


#endif

