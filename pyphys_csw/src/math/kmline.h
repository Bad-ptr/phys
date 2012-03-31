#ifndef K_MLINE_H
#define K_MLINE_H


#include "kmvector.h"


typedef struct kmline23f_s{
	
	kmvect3f b;
	kmvect3f e;
		
} kmline23f;


void	mkline23f_lSet	( kmline23f * to_kl23, kmline23f * _kl23 );

void	mkline23f_vSet	( kmline23f * to_kl23, kmvect3f * f_kv3, kmvect3f * s_kv3 );

void	mkline23f_sSet	( kmline23f * to_kl23, kfloat f_x, kfloat f_y, kfloat f_z, kfloat s_x, kfloat s_y, kfloat s_z );

void	mkline23f_svSet	( kmline23f * to_kl23, kfloat _x, kfloat _y, kfloat _z, kmvect3f * _kv3 );

void	mkline23f_vsSet	( kmline23f * to_kl23, kmvect3f * _kv3, kfloat _x, kfloat _y, kfloat _z );


void	mkline23f_Dir		( kmvect3f * _dir, kmline23f * _kl23 );

void	mkline23f_nnDir		( kmvect3f * _dir, kmline23f * _kl23 );

kfloat	mkline23f_sqLength	( kmline23f * _kl23 );

kfloat	mkline23f_Length		( kmline23f * _kl23 );

kfloat	mkline23f_vDistance	( kmline23f * _kl23, kmvect3f * _kv3 );


#endif

