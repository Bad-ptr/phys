#ifndef K_MMATRIX_H
#define K_MMATRIX_H


#include <math.h>

#include "kmath.h"
#include "kmvector.h"


typedef struct kmmat33f_s{

	kfloat	m11,m12,m13,
			m21,m22,m23,
			m31,m32,m33;
	
} kmmat33f;


void	kmmat33f_zero	( kmmat33f * _km33 );

void	kmmat33f_sset	( kmmat33f * _km33, kfloat _e11, kfloat _e12, kfloat _e13, kfloat _e21, kfloat _e22, kfloat _e23, kfloat _e31, kfloat _e32, kfloat _e33 );

void	kmmat33f_mset	( kmmat33f * to_km33, kmmat33f * from_km33 );


kfloat	kmmat33f_det		( kmmat33f * _km33 );


void	kmmat33f_transpose	( kmmat33f * to_km33, kmmat33f * _km33 );

kfloat	kmmat33f_inverse		( kmmat33f * to_km33, kmmat33f * _km33 );


void	kmmat33f_madd	( kmmat33f * to_km33, kmmat33f * f_km33, kmmat33f * s_km33 );

void	kmmat33f_msub	( kmmat33f * to_km33, kmmat33f * f_km33, kmmat33f * s_km33 );


void	kmmat33f_smul	( kmmat33f * to_km33, kmmat33f * _km33, kfloat s );

void	kmmat33f_sdiv	( kmmat33f * to_km33, kmmat33f * _km33, kfloat s );

void	kmmat33f_mmul	( kmmat33f * to_km33, kmmat33f * f_km33, kmmat33f * s_km33 );

void	kmmat33f_vmul	( kmmat33f * to_km33, kmmat33f * _km33, kmvect3f * _kv3 );


#endif

