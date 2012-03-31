#include "kmvector.h"


void	kmvect3f_vadd	( kmvect3f * to_kv3, kmvect3f * _kv3_u, kmvect3f * _kv3_v ){

	to_kv3->x = _kv3_u->x + _kv3_v->x;
	to_kv3->y = _kv3_u->y + _kv3_v->y;
	to_kv3->z = _kv3_u->z + _kv3_v->z;
	
};

void	kmvect3f_sadd	( kmvect3f * to_kv3, kmvect3f * _kv3, kfloat s ){

	to_kv3->x = _kv3->x + s;
	to_kv3->y = _kv3->y + s;
	to_kv3->z = _kv3->z + s;
	
};


void	kmvect3f_vsub	( kmvect3f * to_kv3, kmvect3f * _kv3_u, kmvect3f * _kv3_v ){

	to_kv3->x = _kv3_u->x - _kv3_v->x;
	to_kv3->y = _kv3_u->y - _kv3_v->y;
	to_kv3->z = _kv3_u->z - _kv3_v->z;
	
};

void	kmvect3f_ssub	( kmvect3f * to_kv3, kmvect3f * _kv3, kfloat s ){

	to_kv3->x = _kv3->x - s;
	to_kv3->y = _kv3->y - s;
	to_kv3->z = _kv3->z - s;
	
};


void	kmvect3f_vmul	( kmvect3f * to_kv3, kmvect3f * _kv3_u, kmvect3f * _kv3_v ){

	to_kv3->x = _kv3_u->x * _kv3_v->x;
	to_kv3->y = _kv3_u->y * _kv3_v->y;
	to_kv3->z = _kv3_u->z * _kv3_v->z;
	
};

void	kmvect3f_smul	( kmvect3f * to_kv3, kmvect3f * _kv3, kfloat s ){

	to_kv3->x = _kv3->x * s;
	to_kv3->y = _kv3->y * s;
	to_kv3->z = _kv3->z * s;
	
};


void	kmvect3f_vdiv	( kmvect3f * to_kv3, kmvect3f * _kv3_u, kmvect3f * _kv3_v ){

	to_kv3->x = _kv3_u->x / _kv3_v->x;
	to_kv3->y = _kv3_u->y / _kv3_v->y;
	to_kv3->z = _kv3_u->z / _kv3_v->z;
	
};

void	kmvect3f_sdiv	( kmvect3f * to_kv3, kmvect3f * _kv3, kfloat s ){

	to_kv3->x = _kv3->x / s;
	to_kv3->y = _kv3->y / s;
	to_kv3->z = _kv3->z / s;
	
};


void kmvect3f_sset( kmvect3f * _kv3, kfloat _x, kfloat _y, kfloat _z ){
	
	_kv3->x = _x;
	_kv3->y = _y;
	_kv3->z = _z;
	
};

void kmvect3f_vset( kmvect3f * to_kv3, kmvect3f * from_kv3 ){
	
	to_kv3->x = from_kv3->x;
	to_kv3->y = from_kv3->y;
	to_kv3->z = from_kv3->z;
	
};

void kmvect3f_zero( kmvect3f * _kv3 ){
	
	_kv3->x = ZEROF;
	_kv3->y = ZEROF;
	_kv3->z = ZEROF;
	
};

void kmvect3f_reverse( kmvect3f * to_kv3, kmvect3f * _kv3 ){
	
	to_kv3->x = -_kv3->x;
	to_kv3->y = -_kv3->y;
	to_kv3->z = -_kv3->z;
	
};


kfloat kmvect3f_length( kmvect3f * _kv3 ){
	
	return( ( kfloat )sqrt( _kv3->x * _kv3->x + _kv3->y * _kv3->y + _kv3->z * _kv3->z ) );
	
};

kfloat kmvect3f_sqlength( kmvect3f * _kv3 ){
	
	return( _kv3->x * _kv3->x + _kv3->y * _kv3->y + _kv3->z * _kv3->z );
	
};

kfloat	kmvect3f_distance	( kmvect3f * f_kv3, kmvect3f * s_kv3 ){
	
	kmvect3f kv;
	
	kmvect3f_vsub( &kv, f_kv3, s_kv3 );
	
	return( kmvect3f_length( &kv ) );
	
};

kfloat kmvect3f_normalize( kmvect3f * to_kv3, kmvect3f * _kv3 ){
	
	kfloat length = kmvect3f_length( _kv3 );
	
/*	if( length <= NZEROF ){
	
		length = ONEF;
		
	}else{*/
	
		to_kv3->x = _kv3->x /= length;
		to_kv3->y = _kv3->y /= length;
		to_kv3->z = _kv3->z /= length;
	
/*		if( kfabs( to_kv3->x ) <= NZEROF ){
			
			to_kv3->x = ZEROF;
			
		}
		if( kfabs( to_kv3->y ) <= NZEROF ){
			
			to_kv3->y = ZEROF;
			
		}
		if( kfabs( to_kv3->z ) <= NZEROF ){
			
			to_kv3->z = ZEROF;
			
		}
	
	}*/
	
return( length );

};

void	kmvect3f_perpendicular2d	( kmvect3f * _kv3, kmvect3f * _perpendicular ){
	
	_perpendicular->x = -_kv3->y;
	
	_perpendicular->y = _kv3->x;
	
};


void	kmvect3f_cross	( kmvect3f * to_kv3, kmvect3f * _kv3_u, kmvect3f * _kv3_v ){

	to_kv3->x =  _kv3_u->y * _kv3_v->z - _kv3_u->z * _kv3_v->y;
	to_kv3->y = -_kv3_u->x * _kv3_v->z + _kv3_u->z * _kv3_v->x;
	to_kv3->z =  _kv3_u->x * _kv3_v->y - _kv3_u->y * _kv3_v->x;
	
};

kfloat kmvect3f_dot( kmvect3f * _kv3_u, kmvect3f * _kv3_v ){

	return( _kv3_u->x * _kv3_v->x + _kv3_u->y * _kv3_v->y + _kv3_u->z * _kv3_v->z );
	
};

kfloat	kmvect3f_vproject	( kmvect3f * to_kv3, kmvect3f * _kv3, kmvect3f * _kv3_axis ){
	
	kmvect3f	nv;
	kfloat	rdot;
	
	kmvect3f_normalize( &nv, _kv3_axis );
	
	rdot = kmvect3f_dot( _kv3, &nv );
	
	kmvect3f_smul( to_kv3, &nv, rdot );
	
	return ( rdot );
	
};


