/*%{
#include "../../src/math/kmvector.h"	
%}*/
%include "../../src/math/kmvector.h"

%extend kmvect3f
{
	
	kmvect3f(){
		kmvect3f *r = malloc( sizeof( kmvect3f ) );
		r->x = 0.0f;
		r->y = 0.0f;
		r->z = 0.0f;
		return r;
	};
	
	kmvect3f( float _x, float _y, float _z ){
		kmvect3f *r = malloc( sizeof( kmvect3f ) );
		r->x = _x;
		r->y = _y;
		r->z = _z;
		return r;
	};

	kmvect3f( kmvect3f * _v ){
		kmvect3f *r = malloc( sizeof( kmvect3f ) );
		r->x = _v->x;
		r->y = _v->y;
		r->z = _v->z;
		return r;
	};
	
	kmvect3f( PyObject * _v ){
		kmvect3f *r = malloc( sizeof( kmvect3f ) );
		
		r->x = 0.0f;
		r->y = 0.0f;
		r->z = 0.0f;
		
		PyObject * iterator = PyObject_GetIter( _v );
		PyObject * item;
		if( NULL == iterator )
			return NULL;

		if( NULL != (item = PyIter_Next( iterator )) ){
			r->x = PyFloat_AS_DOUBLE( item );
			Py_DECREF( item );
		
			if( NULL != (item = PyIter_Next( iterator )) ){
				r->y = PyFloat_AS_DOUBLE( item );
				Py_DECREF( item );
			
				if( NULL != (item = PyIter_Next( iterator )) ){
					r->z = PyFloat_AS_DOUBLE( item );
					Py_DECREF( item );
				}
			}
		}
		
		Py_DECREF( iterator );
		return r;
	};
	
/*	~kmvect3f(){
		free( $self );
	};*/
	
/*	void delandfree(){
		free( $self );
	};
%pythoncode %{
	def __del__( $self ):
			delandfree( $self )
%}*/

//%newobject __str__;
	char * __str__(){
		static char tmp[1024];
		sprintf( tmp,"Vector( %g, %g, %g )", $self->x, $self->y, $self->z );
		return tmp;
	};
	

%newobject vAdd;
%newobject vSub;
%newobject vMul;
%newobject vDiv;
%newobject sAdd;
%newobject sSub;
%newobject sMul;
%newobject sDiv;
%newobject Reverse;
%newobject Norm;
%newobject Perpendicular2d;
%newobject Cross;
%newobject vProject;

	kmvect3f *	vAdd	( kmvect3f * _kv3_v ){
		kmvect3f *r = malloc( sizeof( kmvect3f ) );
		kmvect3f_vadd( r, $self, _kv3_v );
		return r;
	};

	kmvect3f *	sAdd	( kfloat s ){
		kmvect3f *r = malloc( sizeof( kmvect3f ) );
		kmvect3f_sadd( r, $self, s );
		return r;
	};

	kmvect3f *	vSub	( kmvect3f * _kv3_v ){
		kmvect3f *r = malloc( sizeof( kmvect3f ) );
		kmvect3f_vsub( r, $self, _kv3_v );
		return r;
	};

	kmvect3f *	sSub	( kfloat s ){
		kmvect3f *r = malloc( sizeof( kmvect3f ) );
		kmvect3f_ssub( r, $self, s );
		return r;
	};

	kmvect3f *	vMul	( kmvect3f * _kv3_v ){
		kmvect3f *r = malloc( sizeof( kmvect3f ) );
		kmvect3f_vmul( r, $self, _kv3_v );
		return r;
	};

	kmvect3f *	sMul	( kfloat s ){
		kmvect3f *r = malloc( sizeof( kmvect3f ) );
		kmvect3f_smul( r, $self, s );
		return r;
	};

	kmvect3f *	vDiv	( kmvect3f * _kv3_v ){
		kmvect3f *r = malloc( sizeof( kmvect3f ) );
		kmvect3f_vdiv( r, $self, _kv3_v );
		return r;
	};

	kmvect3f *	sDiv	( kfloat s ){
		kmvect3f *r = malloc( sizeof( kmvect3f ) );
		kmvect3f_sdiv( r, $self, s );
		return r;
	};

	void	sSet		( kfloat _x, kfloat _y, kfloat _z ){
		kmvect3f_sset( $self, _x, _y, _z );
	};

	void	vSet		( kmvect3f * from_kv3 ){
		kmvect3f_vset( $self, from_kv3 );
	};

	void	Zero		(  ){
		kmvect3f_zero( $self );
	};

	kmvect3f *	Reverse		(  ){
		kmvect3f *r = malloc( sizeof( kmvect3f ) );
		kmvect3f_reverse( r, $self);
		return r;
	};

	kfloat	Len		(  ){
		return kmvect3f_length( $self );
	};

	kfloat	sqLen	(  ){
		return kmvect3f_sqlength( $self );
	};

	kfloat	Distance	( kmvect3f * s_kv3 ){
		return kmvect3f_distance( $self, s_kv3 );
	};

	kmvect3f *	Norm(  ){
		kmvect3f *r = malloc( sizeof( kmvect3f ) );
		kmvect3f_normalize( r, $self );
		return r;
	};

	kmvect3f *	Perpendicular2d	(  ){
		kmvect3f *r = malloc( sizeof( kmvect3f ) );
		kmvect3f_perpendicular2d( r, $self );
		return r;
	};

	kmvect3f *	Cross	( kmvect3f * _kv3_v ){
		kmvect3f *r = malloc( sizeof( kmvect3f ) );
		kmvect3f_cross( r, $self, _kv3_v );
		return r;
	};

	kfloat	Dot		( kmvect3f * _kv3_v ){
		return kmvect3f_dot( $self, _kv3_v );
	};

	kmvect3f *	vProject	( kmvect3f * _kv3_axis ){
		kmvect3f *r = malloc( sizeof( kmvect3f ) );
		kmvect3f_vproject( r, $self, _kv3_axis );
		return r;
	};
};
