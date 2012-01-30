/*
 * kmath.c
 *
 *  Created on: 21.07.2011
 *      Author: constantin
 */

#include "kmath.h"
#include <stdlib.h>
#include <time.h>


float FastInvSqrt( float x )
{
	  float xhalf = 0.5f*x;
	  int i = *(int*)&x; // get bits for floating value
	  i = 0x5f375a86- (i>>1); // gives initial guess y0
	  x = *(float*)&i; // convert bits back to float
	  x = x*(1.5f-xhalf*x*x); // Newton step, repeating increases accuracy
	  return x;
}


float RandomNum(float x1)
{
	float r = (float)rand();
	r = r/RAND_MAX;
	return r * x1;
}

float FRandomNum(float x0, float x1)
{
	float r = (float)rand();
	r = r/RAND_MAX;
	return r * (x1-x0) + x0;
}

float DegToRad(float deg){
	return deg * M_PI / 180;
};

float RadToDeg(float rad){
	return rad * 180/M_PI;
}
