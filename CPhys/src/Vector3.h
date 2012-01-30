/*
 * Vector3.h
 *
 *  Created on: 21.07.2011
 *      Author: constantin
 */

#ifndef VECTOR3_H_
#define VECTOR3_H_


typedef struct Vector3_s
{
	float x, y,z;
} Vector3_t;

typedef float vec3[3];

Vector3_t * Vector3_new(Vector3_t * v);
Vector3_t * Vector3_Init(Vector3_t * v, float x, float y, float z);
Vector3_t * Vector3_fInit(float x, float y, float z);

Vector3_t * Vector3_Add(Vector3_t *u, Vector3_t *v);
Vector3_t * Vector3_Sub(Vector3_t *u, Vector3_t *v);
Vector3_t * Vector3_Mul(Vector3_t *u, Vector3_t *v);
Vector3_t * Vector3_Div(Vector3_t *u, Vector3_t *v);

Vector3_t * Vector3_sAdd(Vector3_t *v, float s);
Vector3_t * Vector3_sSub(Vector3_t *v, float s);
Vector3_t * Vector3_sMul(Vector3_t *v, float s);
Vector3_t * Vector3_sDiv(Vector3_t *v, float s);

Vector3_t * Vector3_Adda(Vector3_t *u, Vector3_t *v);
Vector3_t * Vector3_Suba(Vector3_t *u, Vector3_t *v);
Vector3_t * Vector3_Mula(Vector3_t *u, Vector3_t *v);
Vector3_t * Vector3_Diva(Vector3_t *u, Vector3_t *v);

Vector3_t * Vector3_sAdda(Vector3_t *v, float s);
Vector3_t * Vector3_sSuba(Vector3_t *v, float s);
Vector3_t * Vector3_sMula(Vector3_t *v, float s);
Vector3_t * Vector3_sDiva(Vector3_t *v, float s);


float Vector3_Len(Vector3_t *v);
float Vector3_InvLen(Vector3_t *v);
Vector3_t * Vector3_Norm(Vector3_t *v);
float Vector3_Norma(Vector3_t *v);
float Vector3_Dot(Vector3_t *u, Vector3_t *v);

void* Vector3_Destroy(Vector3_t *v);

#endif /* VECTOR2_H_ */
