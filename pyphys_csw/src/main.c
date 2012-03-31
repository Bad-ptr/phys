//#include <stdio.h>
//#include <string.h>

#include	"shared/shared.h"
#include	"graphics/gshared.h"
#include	"math/kmvector.h"
#include 	"math/kmquat.h"
#include 	"math/kmmatrix.h"
#include	"io/terminal.h"
//#include	"shared/kmallocator.h"

#include "shared/khashs.h"
#include "shared/kdllist.h"



kbool kmvect3f_print( kmvect3f * _v )
{
	if( !_v )
		return kfalse;

	printf( "kmvect3f( x = %f, y = %f, z = %f );\n", _v->x, _v->y, _v->z );
	printf("lolol\n");

	return ktrue;

};

int	main	( int argc, char *argv[] )
{
	unsigned int iminbl = 1;

	if( argc <= 1 )
	{
		iminbl = 10;
	}
	else iminbl = atoi(argv[1]);

/*
FILE *fco;
fco = fopen("chrs.txt","w");

for (chr = 1; chr < 255; chr++)
{

	fwrite(&chr,sizeof(char),1,fco);
	fprintf(fco,"\n");

}

fclose(fco);
exit(0);
*/


	kmvect3f * varray;
	varray = malloc( sizeof( kmvect3f ) * iminbl );
	kmvect3f_sset( &varray[0], 0.01, 1.01, 4.01 );

/*	int i;
	for( i = 0; i < iminbl; i++ )
		varray[i] = malloc(sizeof(kmvect3f));
*/
	khtable * htable = khtable_init( NULL, &kdllist_class, 9,
			CHASHF(mstringhash), CCMPF(strcmp) );
	khtable_ins_set( htable, "trololo|data1", ":)", strlen(":)") );
	khtable_ins_set( htable, "tralala|data2", "data2", strlen("data2") );
	khtable_ins_set( htable, &varray[0], "kmvect3f", strlen("kmvect3f") );

	printf(
			"%s, %s\n",
			(char *)khtable_get( htable, ":)", 0 ),
			(char *)khtable_get( htable, "data2", 0)
	);

	kmvect3f_print( khtable_get( htable, "kmvect3f", 0 ) );

	printf("===============================================\n");

	int k = 30;
	khtable_ins_set( htable, &k, ":)", strlen(":)") );
	khtable_rm( htable, "kmvect3f", 0 );

	printf(
			"%d, %s\n",
			*(int *)khtable_get( htable, ":)", 0 ),
			(char *)khtable_get( htable, "data2", 0)
	);


	kmvect3f_print( khtable_get( htable, "kmvect3f", 0 ) );

	khtable_destroy( htable );
	free( varray );
	//printf("sizeof double = %d;\nresult = %d;\n", (int)sizeof( double ), result );
	//kmemblob kmblb;
	//printf("address of kmblb = %lu;\naddress of kmblb.p = %lu;\n", &kmblb, &kmblb.p );

	return( 0 );
};

