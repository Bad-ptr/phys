/*
 * Vector2.c
 *
 *  Created on: 21.07.2011
 *      Author: constantin
 */

#include "Vector2.h"
#include "kmath.h"
#include <malloc.h>

Vector2_t * Vector2_new(Vector2_t * v)
{
	Vector2_t *ret = (Vector2_t*)malloc(sizeof(Vector2_t));
	if(!v)
	{
		ret->x = ret->y = 0.0f;
	}
	else
	{
		ret->x = v->x;
		ret->y = v->y;
	}

	return ret;

}
Vector2_t * Vector2_Init(Vector2_t * v, float x, float y)
{
	if(!v)
		v = (Vector2_t*)malloc(sizeof(Vector2_t));

	v->x = x;
	v->y = y;

	return v;
}
Vector2_t * Vector2_fInit(float x, float y)
{
	Vector2_t *v = (Vector2_t*)malloc(sizeof(Vector2_t));

	v->x = x;
	v->y = y;

	return v;
}


Vector2_t * Vector2_Add(Vector2_t *u, Vector2_t *v)
{
	return Vector2_fInit(u->x + v->x, u->y + v->y);
}
Vector2_t * Vector2_Sub(Vector2_t *u, Vector2_t *v)
{
	return Vector2_fInit(u->x - v->x, u->y - v->y);
}
Vector2_t * Vector2_Mul(Vector2_t *u, Vector2_t *v)
{
	return Vector2_fInit(u->x + v->x, u->y + v->y);
}
Vector2_t * Vector2_Div(Vector2_t *u, Vector2_t *v)
{
	return Vector2_fInit(u->x + v->x, u->y + v->y);
}

Vector2_t * Vector2_sAdd(Vector2_t *v, float s)
{
	return Vector2_fInit(v->x+s, v->y+s);
}
Vector2_t * Vector2_sSub(Vector2_t *v, float s)
{
	return Vector2_fInit(v->x-s, v->y-s);
}
Vector2_t * Vector2_sMul(Vector2_t *v, float s)
{
	return Vector2_fInit(v->x*s, v->y*s);
}
Vector2_t * Vector2_sDiv(Vector2_t *v, float s)
{
	return Vector2_fInit(v->x/s, v->y/s);
}

Vector2_t * Vector2_Adda(Vector2_t *u, Vector2_t *v)
{
	u->x += v->x;
	u->y += v->y;

	return u;
}
Vector2_t * Vector2_Suba(Vector2_t *u, Vector2_t *v)
{
	u->x -= v->y;
	u->y -= v->y;

	return u;
}
Vector2_t * Vector2_Mula(Vector2_t *u, Vector2_t *v)
{
	u->x *= v->y;
	u->y *= v->y;

	return u;
}
Vector2_t * Vector2_Diva(Vector2_t *u, Vector2_t *v)
{
	u->x /= v->y;
	u->y /= v->y;

	return u;
}

Vector2_t * Vector2_sAdda(Vector2_t *v, float s)
{
	v->x += s;
	v->y += s;

	return v;
}
Vector2_t * Vector2_sSuba(Vector2_t *v, float s)
{
	v->x -= s;
	v->y -= s;

	return v;
}
Vector2_t * Vector2_sMula(Vector2_t *v, float s)
{
	v->x *= s;
	v->y *= s;

	return v;
}
Vector2_t * Vector2_sDiva(Vector2_t *v, float s)
{
	v->x /= s;
	v->y /= s;

	return v;
}


float Vector2_Len(Vector2_t *v)
{
	return sqrt( v->x * v->x + v->y * v->y );
}
float Vector2_InvLen(Vector2_t *v)
{
	return FastInvSqrt( v->x * v->x + v->y * v->y );
}
Vector2_t * Vector2_Norm(Vector2_t *v)
{
	float il = Vector2_InvLen(v);
	return Vector2_fInit( v->x * il, v->y * il);
}
float Vector2_Norma(Vector2_t *v)
{
	float il = Vector2_InvLen(v);
	Vector2_sMula(v,il);
	return il;
}
float Vector2_Dot(Vector2_t *u, Vector2_t *v)
{
	return u->x * v->x + u->y * v->y;
}

void* Vector2_Destroy( Vector2_t *v )
{
    free(v);

    return NULL;
}
