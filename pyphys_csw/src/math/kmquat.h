#ifndef K_MQUATERNION_H
#define K_MQUATERNION_H


#include <math.h>

#include "kmath.h"
#include "kmmatrix.h"


typedef struct kmquat4f_s{

	kmvect3f v;
	kfloat w;
	
} kmquat4f;


void	kmquat4f_sset		( kmquat4f * to_kq, kfloat _x, kfloat _y, kfloat _z, kfloat _w );

void	kmquat4f_qset		( kmquat4f * to_kq, kmquat4f * from_kqf );

void	kmquat4f_vsset		( kmquat4f * to_kq, kmvect3f * from_kv3, kfloat from_s );

void	kmquat4f_zero		( kmquat4f * _kq );

void	kmquat4f_vinverse	( kmquat4f * to_kq, kmquat4f * _kq );


kfloat	kmquat4f_length		( kmquat4f * _kq );

kfloat	kmquat4f_sqlength	( kmquat4f * _kq );

void	kmquat4f_qadd		( kmquat4f * to_kq, kmquat4f * f_kq, kmquat4f * s_kq );

void	kmquat4f_qsub		( kmquat4f * to_kq, kmquat4f * f_kq, kmquat4f * s_kq );

void	kmquat4f_qmul		( kmquat4f * to_kq, kmquat4f * f_kq, kmquat4f * s_kq );

void	kmquat4f_qvmul		( kmquat4f * to_kq, kmquat4f * _kq, kmvect3f * _kv3 );

void	kmquat4f_vqmul		( kmquat4f * to_kq, kmvect3f * _kv3, kmquat4f * _kq );

void	kmquat4f_smul		( kmquat4f * to_kq, kmquat4f * _kq, kfloat s );

void	kmquat4f_sdiv		( kmquat4f * to_kq, kmquat4f * _kq, kfloat s );


kfloat	kmquat4f_angle	( kmquat4f * _kq );

kfloat	kmquat4f_axis	( kmvect3f * to_kv3_axis, kmquat4f * _kq );

void	kmquat4f_qrotate	( kmquat4f * to_kq, kmquat4f * f_kq, kmquat4f * s_kq );

void kmquat4f_vrotate ( kmvect3f * to_kv3, kmquat4f * _kq, kmvect3f * _kv3 );

void	kmquat4f_easet	( kmquat4f * to_kq, kfloat x, kfloat y, kfloat z );

void	kmquat4f_ea		( kmvect3f * to_kv3, kmquat4f * _kq );


#endif

