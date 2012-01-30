/*
 * Particle.c
 *
 *  Created on: 21.07.2011
 *      Author: constantin
 */

#include "Particle.h"
#include <malloc.h>

Particle_t * Particle_new(Particle_t * p)
{
	Particle_t * ret = malloc(sizeof(Particle_t));
	if(!p)
	{
		ret->pos = ret->oldpos = Vector2_Init(NULL, 0.0f, 0.0f );
		ret->m = 1.0f;
		ret->r = 1.0f;
	}
	else
	{
		ret->pos = p->pos;
		ret->oldpos = p->oldpos;
		ret->m = p->m;
		ret->r = p->r;
	}

	return ret;
}

Particle_t * Particle_Init(Particle_t * p, Vector2_t * pos, Vector2_t * oldpos,
		float m, float r)
{
	if(!p)
		p = malloc(sizeof(Particle_t));
	p->oldpos = oldpos;
	p->pos = pos;
	p->m = m;
	p->r = r;

	return p;

}

Particle_t * Particle_fInit(Vector2_t * pos, float m, float r)
{
	Particle_t * ret = malloc(sizeof(Particle_t));
	ret->oldpos = ret->pos = pos;
	ret->m = m;
	ret->r = r;

	return ret;
}

Particle_t * Particle_fsInit(float x, float y, float m, float r)
{
	Particle_t * ret = malloc(sizeof(Particle_t));
	ret->oldpos = Vector2_fInit(x,y);
	ret->pos = Vector2_fInit(x,y);
	ret->m = m;
	ret->r = r;

	return ret;
}

