/*
 * Vector3.c
 *
 *  Created on: 31.07.3011
 *      Author: constantin
 */

#include "Vector3.h"
#include "kmath.h"
#include <malloc.h>

Vector3_t * Vector3_new(Vector3_t * v)
{
	Vector3_t *ret = (Vector3_t*)malloc(sizeof(Vector3_t));
	if(!v)
	{
		ret->x = ret->y = ret->z = 0.0f;
	}else{
		ret->x = v->x;
        ret->y = v->y;
        ret->z = v->z;
	}

	return ret;

}
Vector3_t * Vector3_Init(Vector3_t * v, float x, float y, float z)
{
	if(!v)
		v = (Vector3_t*)malloc(sizeof(Vector3_t));

	v->x = x;
	v->y = y;
    v->z = z;

	return v;
}
Vector3_t * Vector3_fInit(float x, float y, float z)
{
	Vector3_t *v = (Vector3_t*)malloc(sizeof(Vector3_t));

//http://ompldr.org/vOXFsYQ

	v->x = x;
	v->y = y;
    v->z = z;
	return v;
}


Vector3_t * Vector3_Add(Vector3_t *u, Vector3_t *v)
{
	return Vector3_fInit(u->x + v->x, u->y + v->y, u->z + v->z);
}
Vector3_t * Vector3_Sub(Vector3_t *u, Vector3_t *v)
{
	return Vector3_fInit(u->x - v->x, u->y - v->y, u->z - v->z);
}
Vector3_t * Vector3_Mul(Vector3_t *u, Vector3_t *v)
{
	return Vector3_fInit(u->x * v->x, u->y * v->y, u->z * v->z);
}
Vector3_t * Vector3_Div(Vector3_t *u, Vector3_t *v)
{
	return Vector3_fInit(u->x / v->x, u->y / v->y, u->z / v->z);
}

Vector3_t * Vector3_sAdd(Vector3_t *v, float s)
{
	return Vector3_fInit(v->x + s, v->y + s, v->z + s);
}
Vector3_t * Vector3_sSub(Vector3_t *v, float s)
{
	return Vector3_fInit(v->x - s, v->y - s, v->z - s);
}
Vector3_t * Vector3_sMul(Vector3_t *v, float s)
{
	return Vector3_fInit(v->x * s, v->y * s, v->z * s);
}
Vector3_t * Vector3_sDiv(Vector3_t *v, float s)
{
	return Vector3_fInit(v->x / s, v->y / s, v->z / s);
}

Vector3_t * Vector3_Adda(Vector3_t *u, Vector3_t *v)
{
	u->x += v->x;
	u->y += v->y;
    u->z += v->z;

	return u;
}
Vector3_t * Vector3_Suba(Vector3_t *u, Vector3_t *v)
{
	u->x -= v->y;
	u->y -= v->y;
    u->z -= v->y;

	return u;
}
Vector3_t * Vector3_Mula(Vector3_t *u, Vector3_t *v)
{
	u->x *= v->y;
	u->y *= v->y;
    u->z *= v->z;

	return u;
}
Vector3_t * Vector3_Diva(Vector3_t *u, Vector3_t *v)
{
	u->x /= v->y;
	u->y /= v->y;
    u->z /= v->z;

	return u;
}

Vector3_t * Vector3_sAdda(Vector3_t *v, float s)
{
	v->x += s;
	v->y += s;
    v->z += s;

	return v;
}
Vector3_t * Vector3_sSuba(Vector3_t *v, float s)
{
	v->x -= s;
	v->y -= s;
    v->z -= s;

	return v;
}
Vector3_t * Vector3_sMula(Vector3_t *v, float s)
{
	v->x *= s;
	v->y *= s;
    v->z *= s;

	return v;
}
Vector3_t * Vector3_sDiva(Vector3_t *v, float s)
{
	v->x /= s;
	v->y /= s;
    v->z /= s;

	return v;
}


float Vector3_Len(Vector3_t *v)
{
	return sqrt( v->x * v->x + v->y * v->y + v->z * v->z );
}
float Vector3_InvLen(Vector3_t *v)
{
	return FastInvSqrt( v->x * v->x + v->y * v->y + v->z * v->z );
}
Vector3_t * Vector3_Norm(Vector3_t *v)
{
	float il = Vector3_InvLen(v);
	return Vector3_fInit( v->x * il, v->y * il, v->z * il);
}
float Vector3_Norma(Vector3_t *v)
{
	float il = Vector3_InvLen(v);
	Vector3_sMula(v,il);
	return il;
}
float Vector3_Dot(Vector3_t *u, Vector3_t *v)
{
	return u->x * v->x + u->y * v->y + u->z * u->z;
}

void* Vector3_Destroy( Vector3_t *v )
{
    free(v);

    return NULL;
}
