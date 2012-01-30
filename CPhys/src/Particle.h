/*
 * Particle.h
 *
 *  Created on: 21.07.2011
 *      Author: constantin
 */

#ifndef PARTICLE_H_
#define PARTICLE_H_

#include "Vector2.h"


typedef struct Particle_s
{
	Vector2_t * pos, * oldpos;
	float m, r;
} Particle_t;


Particle_t * Particle_new(Particle_t * p);
Particle_t * Particle_Init(Particle_t * p, Vector2_t * pos, Vector2_t * oldpos,
		float m, float r);
Particle_t * Particle_fInit(Vector2_t * pos, float m, float r);
Particle_t * Particle_fsInit(float x, float y, float m, float r);


#endif /* PARTICLE_H_ */
