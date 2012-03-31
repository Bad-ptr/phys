
#include "kmline.h"


void	mkline23f_lSet	( kmline23f * to_kl23, kmline23f * _kl23 ){
	
	//to_kl23->b.x = _kl23->b.x;	to_kl23->b.y = _kl23->b.y;	to_kl23->b.z = _kl23->b.z;
	//to_kl23->e.x = _kl23->e.x;	to_kl23->e.y = _kl23->e.y;	to_kl23->e.z = _kl23->e.z;
	*to_kl23 = *_kl23;

};

void	mkline23f_vSet	( kmline23f * to_kl23, kmvect3f * f_kv3, kmvect3f * s_kv3 ){
	
	//to_kl23->b.x = f_kv3->x;	to_kl23->b.y = f_kv3->y;	to_kl23->b.z = f_kv3->z;
	//to_kl23->e.x = s_kv3->x;	to_kl23->e.y = s_kv3->y;	to_kl23->e.z = s_kv3->z;
    to_kl23->b = *f_kv3;
    to_kl23->e = *s_kv3;
	
};

void	mkline23f_sSet	( kmline23f * to_kl23, kfloat f_x, kfloat f_y, kfloat f_z, kfloat s_x, kfloat s_y, kfloat s_z ){
	
	to_kl23->b.x = f_x;	to_kl23->b.y = f_y;	to_kl23->b.z = f_z;
	to_kl23->e.x = s_x;	to_kl23->e.y = s_y;	to_kl23->e.z = s_z;
	
};

void	mkline23f_svSet	( kmline23f * to_kl23, kfloat _x, kfloat _y, kfloat _z, kmvect3f * _kv3 ){
	
	to_kl23->b.x = _x;			to_kl23->b.y = _y;			to_kl23->b.z = _z;
	//to_kl23->e.x = _kv3->x;	to_kl23->e.y = _kv3->y;	to_kl23->e.z = _kv3->z;
    to_kl23->e = *_kv3;
	
};

void	mkline23f_vsSet	( kmline23f * to_kl23, kmvect3f * _kv3, kfloat _x, kfloat _y, kfloat _z ){
	
	//to_kl23->b.x = _kv3->x;	to_kl23->b.y = _kv3->y;	to_kl23->b.z = _kv3->z;
	to_kl23->b = *_kv3;
    to_kl23->e.x = _x;			to_kl23->e.y = _y;			to_kl23->e.z = _z;
	
};


void	mkline23f_Dir	( kmvect3f * _dir, kmline23f * _kl23 ){
	
	kmvect3f dkv3;
	
	kmvect3f_vsub( &dkv3, &_kl23->e, &_kl23->b);
	
	kmvect3f_normalize( _dir, &dkv3 );
	
};

void	mkline23f_nnDir	( kmvect3f * _dir, kmline23f * _kl23 ){

	kmvect3f_vsub( _dir, &_kl23->e, &_kl23->b );

}


kfloat	mkline23f_sqLength	( kmline23f * _kl23 ){
	
	kmvect3f dkv3;
	
	kmvect3f_vsub( &dkv3, &_kl23->e, &_kl23->b );
	
	return( kmvect3f_sqlength( &dkv3 ) );
	
};

kfloat	mkline23f_Length    ( kmline23f * _kl23 ){
	
	kmvect3f dkv3;
	
	kmvect3f_vsub( &dkv3, &_kl23->e, &_kl23->b );
	
	return( kmvect3f_length( &dkv3 ) );

	
};

kfloat	mkline23f_vDistance	( kmline23f * _kl23, kmvect3f * _kv3 ){
	
	kmvect3f dkvl, dkvv, pv;
	
	kmvect3f_vsub( &dkvl, &_kl23->e, &_kl23->b);
	
	kmvect3f_vsub( &dkvv, _kv3, &_kl23->b);
	
	kmvect3f_vproject( &pv, &dkvv, &dkvl );
	
	return( kmvect3f_distance( &pv, _kv3 ) );
	
};
 

