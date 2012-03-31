#include	"kmplane.h"


void	mkplane23f_pSet	( kmplane23f * to_kp23, kmplane23f * _kp23 ){
	
	to_kp23->p.x = _kp23->p.x;	to_kp23->p.y = _kp23->p.y;	to_kp23->p.z = _kp23->p.z;
	to_kp23->n.x = _kp23->n.x;	to_kp23->n.y = _kp23->n.y;	to_kp23->n.z = _kp23->n.z;
	
};

void	mkplane23f_vSet	( kmplane23f * to_kp23, kmvect3f * f_kv3, kmvect3f * n_kv3 ){
	
	to_kp23->p.x = f_kv3->x;	to_kp23->p.y = f_kv3->y;	to_kp23->p.z = f_kv3->z;
	to_kp23->n.x = n_kv3->x;	to_kp23->n.y = n_kv3->y;	to_kp23->n.z = n_kv3->z;
	
};

void	mkplane23f_3vSet	( kmplane23f * to_kp23, kmvect3f * f_kv3, kmvect3f * s_kv3, kmvect3f * t_kv3 ){
	
	kmline23f kl1, kl2;
	
	kmvect3f kv, kv1, kv2;
	
	
	kmvect3f_vset( &kl1.b, s_kv3);	kmvect3f_vset( &kl1.e, f_kv3);
	
	mkline23f_Dir( &kv1, &kl1 );
	
	
	kmvect3f_vset( &kl2.b, s_kv3);	kmvect3f_vset( &kl2.e, t_kv3);
	
	mkline23f_Dir( &kv2, &kl2 );
	
	
	kmvect3f_cross( &kv, &kv1, &kv2 );
	
	mkplane23f_vSet( to_kp23, f_kv3, &kv );
	
};

void	mkplane23f_sSet	( kmplane23f * to_kp23, kfloat _x, kfloat _y, kfloat _z, kfloat _nx, kfloat _ny, kfloat _nz ){
	
	to_kp23->p.x = _x;  to_kp23->p.y = _y;  to_kp23->p.z = _z;
	to_kp23->n.x = _nx; to_kp23->n.y = _ny; to_kp23->n.z = _nz;
	
};

kfloat	mkplane23f_vDistance( kmplane23f * _kp23, kmvect3f * _kv3 ){
	
	kmvect3f	dv, rv;
	
	
	kmvect3f_vsub( &dv, _kv3, &_kp23->p );
	
	kmvect3f_vproject( &rv, &dv, &_kp23->n );
	
	return( kmvect3f_length( &rv ) );
	
};

void mkplane23f_vProject( kmvect3f * to_kv3, kmplane23f * _kp23, kmvect3f * _kv3){

	kfloat dist = mkplane23f_vDistance( _kp23, _kv3 );
	
	kmvect3f vd; kmvect3f_smul( &vd, &_kp23->n, dist );

	kmvect3f_vsub( to_kv3, _kv3, &vd );

};

