#include "kmquat.h"


void	kmquat4f_sset		( kmquat4f * to_kq, kfloat _x, kfloat _y, kfloat _z, kfloat _w ){
	
	to_kq->v.x = _x; to_kq->v.y = _y; to_kq->v.z = _z;
	
	to_kq->w = _w;
	
};

void	kmquat4f_qset		( kmquat4f * to_kq, kmquat4f * from_kq ){
	
	to_kq->v.x = from_kq->v.x; to_kq->v.y = from_kq->v.y; to_kq->v.z = from_kq->v.z;
	
	to_kq->w = from_kq->w;
	
};

void	kmquat4f_vsset	( kmquat4f * to_kq, kmvect3f * from_kv3, kfloat from_s ){
	
	to_kq->v.x = from_kv3->x; to_kq->v.y = from_kv3->y; to_kq->v.z = from_kv3->z;
	
	to_kq->w = from_s;
	
};

void	kmquat4f_zero		( kmquat4f * _kq ){
	
	_kq->v.x = ZEROF; _kq->v.y = ZEROF; _kq->v.z = ZEROF;
	
	_kq->w = ZEROF;
	
};

void	kmquat4f_vinverse	( kmquat4f * to_kq, kmquat4f * _kq ){
	
	to_kq->v.x = -_kq->v.x; to_kq->v.y = -_kq->v.y; to_kq->v.z = -_kq->v.z;
	
	to_kq->w = _kq->w;
	
};


kfloat	kmquat4f_length	( kmquat4f * _kq ){
	
	return( (kfloat)sqrt( _kq->v.x * _kq->v.x + _kq->v.y * _kq->v.y + _kq->v.z * _kq->v.z + _kq->w * _kq->w ) );
	
};

kfloat	kmquat4f_sqlength	( kmquat4f * _kq ){
	
	return( _kq->v.x * _kq->v.x + _kq->v.y * _kq->v.y + _kq->v.z * _kq->v.z + _kq->w * _kq->w );
	
};


void	kmquat4f_qadd		( kmquat4f * to_kq, kmquat4f * f_kq, kmquat4f * s_kq ){
	
	to_kq->v.x = f_kq->v.x + s_kq->v.x; to_kq->v.y = f_kq->v.y + s_kq->v.y; to_kq->v.z = f_kq->v.z + s_kq->v.z;
	
	to_kq->w = f_kq->w + s_kq->w;
	
};
 
void	kmquat4f_qsub		( kmquat4f * to_kq, kmquat4f * f_kq, kmquat4f * s_kq ){
	
	to_kq->v.x = f_kq->v.x - s_kq->v.x; to_kq->v.y = f_kq->v.y - s_kq->v.y; to_kq->v.z = f_kq->v.z - s_kq->v.z;
	
	to_kq->w = f_kq->w - s_kq->w;
	
};

void	kmquat4f_qmul		( kmquat4f * to_kq, kmquat4f * f_kq, kmquat4f * s_kq ){
	
	kmquat4f_sset( to_kq, f_kq->w * s_kq->v.x + f_kq->v.x * s_kq->w + f_kq->v.y * s_kq->v.z - f_kq->v.z * s_kq->v.y,
						f_kq->w * s_kq->v.y + f_kq->v.y * s_kq->w + f_kq->v.z * s_kq->v.x - f_kq->v.x * s_kq->v.z,
						f_kq->w * s_kq->v.z + f_kq->v.z * s_kq->w + f_kq->v.x * s_kq->v.y - f_kq->v.y * s_kq->v.x,
						f_kq->w * s_kq->w - f_kq->v.x * s_kq->v.x - f_kq->v.y * s_kq->v.y - f_kq->v.z * s_kq->v.z );
	
};

void	kmquat4f_qvmul	( kmquat4f * to_kq, kmquat4f * _kq, kmvect3f * _kv3 ){
	
	kmquat4f_sset( to_kq, _kq->w * _kv3->x + _kq->v.y * _kv3->z - _kq->v.z * _kv3->y,
						_kq->w * _kv3->y + _kq->v.z * _kv3->x - _kq->v.x * _kv3->z,
						_kq->w * _kv3->z + _kq->v.x * _kv3->y - _kq->v.y * _kv3->x,
						-( _kq->v.x * _kv3->x - _kq->v.y * _kv3->y - _kq->v.z * _kv3->z ) );
	
};

void	kmquat4f_vqmul	( kmquat4f * to_kq, kmvect3f * _kv3, kmquat4f * _kq ){
	
	kmquat4f_sset( to_kq, _kv3->x * _kq->w + _kv3->y * _kq->v.z - _kv3->z * _kq->v.y,
						_kv3->y * _kq->w + _kv3->z * _kq->v.x - _kv3->x * _kq->v.z,
						_kv3->z * _kq->w + _kv3->x * _kq->v.y - _kv3->y * _kq->v.x,
						-( _kv3->x * _kq->v.x - _kv3->y * _kq->v.y - _kv3->z * _kq->v.z ) );
	
};

void	kmquat4f_smul		( kmquat4f * to_kq, kmquat4f * _kq, kfloat s ){
	
	to_kq->v.x = _kq->v.x * s; to_kq->v.y = _kq->v.y * s; to_kq->v.z = _kq->v.z * s;
	
	to_kq->w = _kq->w * s;
	
};

void	kmquat4f_sdiv		( kmquat4f * to_kq, kmquat4f * _kq, kfloat s ){
	
	to_kq->v.x = _kq->v.x / s; to_kq->v.y = _kq->v.y / s; to_kq->v.z = _kq->v.z / s;
	
	to_kq->w = _kq->w / s;
	
};


kfloat	kmquat4f_angle	( kmquat4f * _kq ){
	
	return( (kfloat)( 2 * acos( _kq->w ) ) );
	
};

kfloat	kmquat4f_axis	( kmvect3f * to_kv3_axis, kmquat4f * _kq ){
	
	kfloat length = kmvect3f_length( &_kq->v );
	
/*	if ( length <= NZEROF ){
		
		kmvect3f_zero( to_kv3_axis );
		
	}else{*/
		
		kmvect3f_sdiv( to_kv3_axis, &_kq->v, length );
		
//	}
	
	return( length );
	
};

void	kmquat4f_qrotate	( kmquat4f * to_kq, kmquat4f * f_kq, kmquat4f * s_kq ){
	
	kmquat4f invq;
	
	kmquat4f_vinverse( &invq, f_kq );
	
	kmquat4f_qmul( to_kq, f_kq, s_kq );
	
	kmquat4f_qmul( to_kq, to_kq, &invq );
	
};

void kmquat4f_vrotate ( kmvect3f * to_kv3, kmquat4f * _kq, kmvect3f * _kv3 ){
	
	kmquat4f invq, qvmul;
	
	kmquat4f_vinverse( &invq, _kq );
	
	kmquat4f_qvmul( &qvmul, _kq, _kv3 );
	
	kmquat4f_qmul( &qvmul, &qvmul, &invq );
	
	kmvect3f_vset( to_kv3, &qvmul.v );
	
};

void	kmquat4f_easet	( kmquat4f * to_kq, kfloat x, kfloat y, kfloat z ){
	
	DEFCMATHTYPE roll = deg2rad( x );
	
	DEFCMATHTYPE pitch = deg2rad( y );
	
	DEFCMATHTYPE yaw = deg2rad( z );
	
	DEFCMATHTYPE cyaw, cpitch, croll, syaw, spitch, sroll;
	
	DEFCMATHTYPE cyawcpitch, syawspitch, cyawspitch, syawcpitch;
	
	
	cyaw = cos( 0.5f * yaw );
	
	cpitch = cos( 0.5f * pitch );
	
	croll = cos( 0.5f * roll );
	
	syaw = sin( 0.5f * yaw );
	
	spitch = sin( 0.5f * pitch );
	
	sroll = sin( 0.5f * roll );
	
	
	cyawcpitch = cyaw * cpitch;
	
	syawspitch = syaw * spitch;
	
	cyawspitch = cyaw * spitch;
	
	syawcpitch = syaw * cpitch;
	
	
	to_kq->v.x = ( kfloat )( cyawcpitch * sroll - syawspitch * croll );
	
	to_kq->v.y = ( kfloat )( cyawspitch * croll + syawcpitch * sroll );
	
	to_kq->v.z = ( kfloat )( syawcpitch * croll - cyawspitch * sroll );
	
	to_kq->w = ( kfloat )( cyawcpitch * croll + syawspitch * sroll );
	
};

void	kmquat4f_ea( kmvect3f * to_kv3, kmquat4f * _kq ){
	
	DEFCMATHTYPE r11, r21, r31, r32, r33, r12, r13;
	
	DEFCMATHTYPE qxx, qyy, qzz, qww;
	
	DEFCMATHTYPE fabsr31;
	
	
	qxx = _kq->v.x * _kq->v.x;
	
	qyy = _kq->v.y * _kq->v.y;
	
	qzz = _kq->v.z * _kq->v.z;
	
	qww = _kq->w * _kq->w;
	
	
	r11 = qww + qxx - qyy - qzz;
	
	r21 = 2 * ( _kq->v.x * _kq->v.y + _kq->w * _kq->v.z );
	
	r31 = 2 * ( _kq->v.x * _kq->v.z - _kq->w * _kq->v.y );
	
	r32 = 2 * ( _kq->v.y * _kq->v.z + _kq->w * _kq->v.x);
	
	r33 = qww - qxx - qyy + qzz;
	
	
	fabsr31 = kfabs( r31 );
	
	if( fabsr31 > 0.999999 ){
		
		r12 = 2 * ( _kq->v.x * _kq->v.y - _kq->w * _kq->v.z );
		
		r13 = 2 * ( _kq->v.x * _kq->v.z + _kq->w * _kq->v.y );
		
		
		to_kv3->x = rad2deg( ZEROF ); //roll
		
		to_kv3->y = rad2deg( ( kfloat )( - ( M_PI/2 ) * r31/fabsr31 ) ); //pitch
		
		to_kv3->z = rad2deg( ( kfloat )atan2( -r12, -r31*r13 ) ); //yaw
		
		return;
		
	}
	
	to_kv3->x = rad2deg( ( kfloat )atan2( r32, r33 ) ); //roll
	
	to_kv3->y = rad2deg( ( kfloat )asin( -r31 ) ); //pitch
	
	to_kv3->z = rad2deg( ( kfloat )atan2( r21, r11 ) ); //yaw
	
};


