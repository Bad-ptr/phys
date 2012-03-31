#ifndef	K_MVECTORS_H
#define	K_MVECTORS_H


#include	<math.h>

#include	"kmath.h"


typedef	struct	kmvect3f_s{
	
	kfloat	x,y,z;
	
} kmvect3f;


void	kmvect3f_vadd	( kmvect3f * to_kv3, kmvect3f * _kv3_u, kmvect3f * _kv3_v );

void	kmvect3f_sadd	( kmvect3f * to_kv3, kmvect3f * _kv3, kfloat s );


void	kmvect3f_vsub	( kmvect3f * to_kv3, kmvect3f * _kv3_u, kmvect3f * _kv3_v );

void	kmvect3f_ssub	( kmvect3f * to_kv3, kmvect3f * _kv3, kfloat s );


void	kmvect3f_vmul	( kmvect3f * to_kv3, kmvect3f * _kv3_u, kmvect3f * _kv3_v );

void	kmvect3f_smul	( kmvect3f * to_kv3, kmvect3f * _kv3, kfloat s );


void	kmvect3f_vdiv	( kmvect3f * to_kv3, kmvect3f * _kv3_u, kmvect3f * _kv3_v );

void	kmvect3f_sdiv	( kmvect3f * to_kv3, kmvect3f * _kv3, kfloat s );


void	kmvect3f_sset		( kmvect3f * _kv3,kfloat _x,kfloat _y, kfloat _z );

void	kmvect3f_vset		( kmvect3f * to_kv3, kmvect3f * from_kv3 );

void	kmvect3f_zero		( kmvect3f * _kv3 );

void	kmvect3f_reverse		( kmvect3f * to_kv3, kmvect3f * _kv3 );


kfloat	kmvect3f_length		( kmvect3f * _kv3 );

kfloat	kmvect3f_sqlength	( kmvect3f * _kv3 );

kfloat	kmvect3f_distance	( kmvect3f * f_kv3, kmvect3f * s_kv3 );

kfloat	kmvect3f_normalize	( kmvect3f * to_kv3, kmvect3f * _kv3 );

void	kmvect3f_perpendicular2d	( kmvect3f * _kv3, kmvect3f * _perpendicular );


void	kmvect3f_cross	( kmvect3f * to_kv3, kmvect3f * _kv3_u, kmvect3f * _kv3_v );

kfloat	kmvect3f_dot		( kmvect3f * _kv3_u, kmvect3f * _kv3_v );

kfloat	kmvect3f_vproject	( kmvect3f * to_kv3, kmvect3f * _kv3, kmvect3f * _kv3_axis );


#endif

