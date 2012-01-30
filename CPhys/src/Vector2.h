/*
 * Vector2.h
 *
 *  Created on: 21.07.2011
 *      Author: constantin
 */

#ifndef VECTOR2_H_
#define VECTOR2_H_


typedef struct Vector2_s
{
	float x, y;
} Vector2_t;

typedef float vec2[2];

Vector2_t * Vector2_new(Vector2_t * v);
Vector2_t * Vector2_Init(Vector2_t * v, float x, float y);
Vector2_t * Vector2_fInit(float x, float y);

Vector2_t * Vector2_Add(Vector2_t *u, Vector2_t *v);
Vector2_t * Vector2_Sub(Vector2_t *u, Vector2_t *v);
Vector2_t * Vector2_Mul(Vector2_t *u, Vector2_t *v);
Vector2_t * Vector2_Div(Vector2_t *u, Vector2_t *v);

Vector2_t * Vector2_sAdd(Vector2_t *v, float s);
Vector2_t * Vector2_sSub(Vector2_t *v, float s);
Vector2_t * Vector2_sMul(Vector2_t *v, float s);
Vector2_t * Vector2_sDiv(Vector2_t *v, float s);

Vector2_t * Vector2_Adda(Vector2_t *u, Vector2_t *v);
Vector2_t * Vector2_Suba(Vector2_t *u, Vector2_t *v);
Vector2_t * Vector2_Mula(Vector2_t *u, Vector2_t *v);
Vector2_t * Vector2_Diva(Vector2_t *u, Vector2_t *v);

Vector2_t * Vector2_sAdda(Vector2_t *v, float s);
Vector2_t * Vector2_sSuba(Vector2_t *v, float s);
Vector2_t * Vector2_sMula(Vector2_t *v, float s);
Vector2_t * Vector2_sDiva(Vector2_t *v, float s);


float Vector2_Len(Vector2_t *v);
float Vector2_InvLen(Vector2_t *v);
Vector2_t * Vector2_Norm(Vector2_t *v);
float Vector2_Norma(Vector2_t *v);
float Vector2_Dot(Vector2_t *u, Vector2_t *v);

void* Vector2_Destroy(Vector2_t *v);

#endif /* VECTOR2_H_ */
