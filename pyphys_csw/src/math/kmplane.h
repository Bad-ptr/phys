#ifndef	K_MPLANE_H
#define	K_MPLANE_H


#include	"../shared/shared.h"

#include	"./kmvector.h"
#include	"./kmline.h"

typedef struct kmplane23f_s{
	
	kmvect3f p;
	kmvect3f n;
	
} kmplane23f;


void	mkplane23f_pSet	( kmplane23f * to_kp23, kmplane23f * _kp23 );

void	mkplane23f_vSet	( kmplane23f * to_kp23, kmvect3f * f_kv3, kmvect3f * n_kv3 );

void	mkplane23f_3vSet	( kmplane23f * to_kp23, kmvect3f * f_kv3, kmvect3f * s_kv3, kmvect3f * t_kv3 );

void	mkplane23f_sSet	( kmplane23f * to_kp23, kfloat _x, kfloat _y, kfloat _z, kfloat _nx, kfloat _ny, kfloat _nz );

kfloat	mkplane23f_vDistance( kmplane23f * _kp23, kmvect3f * _kv3 );

void mkplane23f_vProject( kmvect3f * to_kv3, kmplane23f * _kp23, kmvect3f * _kv3);

#endif

