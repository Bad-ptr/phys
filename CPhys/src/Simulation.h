/*
 * Simulation.h
 *
 *  Created on: 21.07.2011
 *      Author: constantin
 */

#ifndef SIMULATION_H_
#define SIMULATION_H_

#include "Llist.h"
#include "Vector2.h"


typedef struct Simulation_s
{
	Vector2_t *b0, *b1;
	Llist_t * particles;
	int nump;
} Simulation_t;


Simulation_t * Simulation_new(Simulation_t * s);
Simulation_t * Simulation_Init(Simulation_t * s, Vector2_t * b0, Vector2_t * b1,
		Llist_t * particles);
Simulation_t * Simulation_fInit(Vector2_t * b0, Vector2_t * b1,
		Llist_t * particles);
Simulation_t * Simulation_wflInit(Vector2_t * b1);
Simulation_t * Simulation_wflsInit(float x, float y);
Simulation_t * Simulation_pAdd(Simulation_t * s, void * particle );
Simulation_t * Simulation_Rand(Simulation_t * s, int pnum);
Simulation_t * Simulation_Upd(Simulation_t * s, float dt);


#endif /* SIMULATION_H_ */
