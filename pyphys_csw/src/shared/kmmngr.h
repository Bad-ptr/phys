#ifndef K_MMNGR_H
#define K_MMNGR_H


#include "shared.h"
#include "khashs.h"

struct kmmngr_s;

typedef struct kmemblob_s
{
	KID nsize;
	ksize objsize;
	struct kmmngr_s * pmngr;

}kmemblob;

typedef struct kmemblock_s
{
	kmemblob * pmemblob;

}kmemblock;

typedef struct kmmngr_s
{
	khtable * blobs;
	KID nfreeblobs_tokeep;

}kmmngr;


#endif

