#include "kmath.h"


kfloat	deg2rad	( kfloat _deg ){
	
	return( _deg * M_PI / 180.0f );
	
};

kfloat	rad2deg	( kfloat _rad ){
	
	return( _rad * 180.0f / M_PI );
	
};

// as ID sowtware teached us ;)
// microsoft's fabs seems to be ungodly slow...
kfloat kfabs( kfloat f ) {
	
	union {
		unsigned int l;
		kfloat f;
	} tmp;
	
	tmp.f = f;
	tmp.l &= 0x7FFFFFFF;
	
	return tmp.f;
	
};



