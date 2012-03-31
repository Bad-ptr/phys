#include "shared.h"

void * kzmalloc( ksize _ksize ){
	void * ptr = malloc( _ksize );
	memset( ptr, 0, _ksize);

	return ptr;
};

