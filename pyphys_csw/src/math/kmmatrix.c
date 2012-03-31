#include "kmmatrix.h"

void	kmmat33f_zero	( kmmat33f * _km33 ){

	_km33->m11 = ZEROF;	_km33->m12 = ZEROF;	_km33->m13 = ZEROF;
	_km33->m21 = ZEROF;	_km33->m22 = ZEROF;	_km33->m23 = ZEROF;
	_km33->m31 = ZEROF;	_km33->m32 = ZEROF;	_km33->m33 = ZEROF;
	
};

void	kmmat33f_sset	( kmmat33f * _km33, kfloat _e11, kfloat _e12, kfloat _e13, kfloat _e21, kfloat _e22, kfloat _e23, kfloat _e31, kfloat _e32, kfloat _e33 ){
	
	_km33->m11 = _e11;		_km33->m12 = _e12;		_km33->m13 = _e13;
	_km33->m21 = _e21;		_km33->m22 = _e22;		_km33->m23 = _e23;
	_km33->m31 = _e31;		_km33->m32 = _e32;		_km33->m33 = _e33;
	
};

void	kmmat33f_mset	( kmmat33f * to_km33, kmmat33f * from_km33 ){
	
	to_km33->m11 = from_km33->m11; to_km33->m12 = from_km33->m12; to_km33->m13 = from_km33->m13;
	to_km33->m21 = from_km33->m21; to_km33->m22 = from_km33->m22; to_km33->m23 = from_km33->m23;
	to_km33->m31 = from_km33->m31; to_km33->m32 = from_km33->m32; to_km33->m33 = from_km33->m33;
	
};


kfloat	kmmat33f_det		( kmmat33f * _km33 ){
	
	return ( _km33->m11 * _km33->m22 * _km33->m33 -
			 _km33->m11 * _km33->m32 * _km33->m23 +
			 _km33->m21 * _km33->m32 * _km33->m13 -
			 _km33->m21 * _km33->m12 * _km33->m33 +
			 _km33->m31 * _km33->m12 * _km33->m23 -
			 _km33->m31 * _km33->m22 * _km33->m13 );
	
};


void	kmmat33f_transpose	( kmmat33f * to_km33, kmmat33f * _km33 ){
	
	kmmat33f_sset( to_km33,	_km33->m11, _km33->m21, _km33->m31, 
							_km33->m12, _km33->m22, _km33->m32, 
							_km33->m13, _km33->m23, _km33->m33 );
	
};

kfloat	kmmat33f_inverse		( kmmat33f * to_km33, kmmat33f * _km33 ){
//попробовать найти и применить метод исключения Гаусса-Джордана->
//"Numerical Recipes for C++"
	kfloat d = kmmat33f_det( _km33 );
	if ( d == ZEROF ) d = ONEF;
	
	kmmat33f_sset ( to_km33,  ( _km33->m22 * _km33->m33 - _km33->m23 * _km33->m32 ) / d,
							-( _km33->m12 * _km33->m33 - _km33->m13 * _km33->m32 ) / d,
							 ( _km33->m12 * _km33->m23 - _km33->m13 * _km33->m22 ) / d,
							-( _km33->m21 * _km33->m33 - _km33->m23 * _km33->m31 ) / d,
							 ( _km33->m11 * _km33->m33 - _km33->m13 * _km33->m31 ) / d,
							-( _km33->m11 * _km33->m23 - _km33->m13 * _km33->m21 ) / d,
							 ( _km33->m21 * _km33->m32 - _km33->m22 * _km33->m31 ) / d,
							-( _km33->m11 * _km33->m32 - _km33->m12 * _km33->m31 ) / d,
							 ( _km33->m11 * _km33->m22 - _km33->m12 * _km33->m21 ) / d );
	
	return( d );
	
};


void	kmmat33f_madd	( kmmat33f * to_km33, kmmat33f * f_km33, kmmat33f * s_km33 ){
	
	to_km33->m11 = f_km33->m11 + s_km33->m11;
	to_km33->m21 = f_km33->m21 + s_km33->m21;
	to_km33->m31 = f_km33->m31 + s_km33->m31;
	
	to_km33->m12 = f_km33->m12 + s_km33->m12;
	to_km33->m22 = f_km33->m22 + s_km33->m22;
	to_km33->m32 = f_km33->m32 + s_km33->m32;
	
	to_km33->m13 = f_km33->m13 + s_km33->m13;
	to_km33->m23 = f_km33->m23 + s_km33->m23;
	to_km33->m33 = f_km33->m33 + s_km33->m33;
	
};

void	kmmat33f_msub	( kmmat33f * to_km33, kmmat33f * f_km33, kmmat33f * s_km33 ){
	
	to_km33->m11 = f_km33->m11 - s_km33->m11;
	to_km33->m21 = f_km33->m21 - s_km33->m21;
	to_km33->m31 = f_km33->m31 - s_km33->m31;
	
	to_km33->m12 = f_km33->m12 - s_km33->m12;
	to_km33->m22 = f_km33->m22 - s_km33->m22;
	to_km33->m32 = f_km33->m32 - s_km33->m32;
	
	to_km33->m13 = f_km33->m13 - s_km33->m13;
	to_km33->m23 = f_km33->m23 - s_km33->m23;
	to_km33->m33 = f_km33->m33 - s_km33->m33;
	
};


void	kmmat33f_smul	( kmmat33f * to_km33, kmmat33f * _km33, kfloat s ){
	
	to_km33->m11 = _km33->m11 * s; to_km33->m12 = _km33->m12 * s; to_km33->m11 = _km33->m13 * s;
	to_km33->m21 = _km33->m21 * s; to_km33->m22 = _km33->m22 * s; to_km33->m22 = _km33->m23 * s;
	to_km33->m31 = _km33->m31 * s; to_km33->m32 = _km33->m32 * s; to_km33->m33 = _km33->m33 * s;
	
};

void	kmmat33f_sdiv	( kmmat33f * to_km33, kmmat33f * _km33, kfloat s ){
	
	to_km33->m11 = _km33->m11 / s; to_km33->m12 = _km33->m12 / s; to_km33->m11 = _km33->m13 / s;
	to_km33->m21 = _km33->m21 / s; to_km33->m22 = _km33->m22 / s; to_km33->m22 = _km33->m23 / s;
	to_km33->m31 = _km33->m31 / s; to_km33->m32 = _km33->m32 / s; to_km33->m33 = _km33->m33 / s;
	
};

void	kmmat33f_mmul	( kmmat33f * to_km33, kmmat33f * f_km33, kmmat33f * s_km33 ){
	
	kmmat33f_sset( to_km33, f_km33->m11 * s_km33->m11 + f_km33->m12 * s_km33->m21 + f_km33->m13 * s_km33->m31,
						   f_km33->m11 * s_km33->m12 + f_km33->m12 * s_km33->m22 + f_km33->m13 * s_km33->m32,
						   f_km33->m11 * s_km33->m13 + f_km33->m12 * s_km33->m23 + f_km33->m13 * s_km33->m33,
						   
						   f_km33->m21 * s_km33->m11 + f_km33->m22 * s_km33->m21 + f_km33->m23 * s_km33->m31,
						   f_km33->m21 * s_km33->m12 + f_km33->m22 * s_km33->m22 + f_km33->m23 * s_km33->m32,
						   f_km33->m21 * s_km33->m13 + f_km33->m22 * s_km33->m23 + f_km33->m23 * s_km33->m33,
						   
						   f_km33->m31 * s_km33->m11 + f_km33->m32 * s_km33->m21 + f_km33->m33 * s_km33->m31,
						   f_km33->m31 * s_km33->m12 + f_km33->m32 * s_km33->m22 + f_km33->m33 * s_km33->m32,
						   f_km33->m31 * s_km33->m13 + f_km33->m32 * s_km33->m23 + f_km33->m33 * s_km33->m33);
	
};

void	kmmat33f_vmul	( kmmat33f * to_km33, kmmat33f * _km33, kmvect3f * _kv3 ){
	
	to_km33->m11 = _km33->m11 * _kv3->x;
	to_km33->m21 = _km33->m21 * _kv3->x;
	to_km33->m31 = _km33->m31 * _kv3->x;
	
	to_km33->m12 = _km33->m12 * _kv3->y;
	to_km33->m22 = _km33->m22 * _kv3->y;
	to_km33->m32 = _km33->m32 * _kv3->y;
	
	to_km33->m13 = _km33->m13 * _kv3->z;
	to_km33->m23 = _km33->m23 * _kv3->z;
	to_km33->m33 = _km33->m33 * _kv3->z;
	
};


