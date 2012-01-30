/*
 * Simulation.c
 *
 *  Created on: 21.07.2011
 *      Author: constantin
 */

#include "Simulation.h"
#include "kmath.h"
#include "Vector2.h"
#include "Particle.h"
#include <malloc.h>


Simulation_t * Simulation_new(Simulation_t * s)
{
	Simulation_t * ret = (Simulation_t *)malloc(sizeof(Simulation_t));
	if(!s)
	{
		ret->b0 = Vector2_fInit(0.0f,0.0f);
		ret->b1 = Vector2_fInit(800.0f,600.0f);
		ret->particles = Llist_fInit(NULL,NULL);
		ret->nump = 0;
	}
	ret->b0 = s->b0;
	ret->b1 = s->b1;
	ret->particles = s->particles;
	ret->nump = s->nump;

	return ret;
}
Simulation_t * Simulation_Init(Simulation_t * s, Vector2_t * b0, Vector2_t * b1,
		Llist_t * particles)
{
	if(!s)
		s = (Simulation_t *)malloc(sizeof(Simulation_t));

	s->b0 = b0;
	s->b1 = b1;
	s->particles = particles;
	s->nump = 0;

	return s;
}
Simulation_t * Simulation_fInit(Vector2_t * b0, Vector2_t * b1,
		Llist_t * particles)
{
	Simulation_t * ret = (Simulation_t *)malloc(sizeof(Simulation_t));
	ret->b0 = b0;
	ret->b1 = b1;
	ret->particles = particles;
	ret->nump = 0;

	return ret;
}
Simulation_t * Simulation_wflInit(Vector2_t * b1)
{
	Simulation_t * ret = (Simulation_t *)malloc(sizeof(Simulation_t));
	ret->b0 = Vector2_fInit(0.0f,0.0f);
	ret->b1 = b1;
	ret->particles = Llist_fInit(NULL,NULL);
	ret->nump = 0;

	return ret;
}
Simulation_t * Simulation_wflsInit(float x, float y)
{
	Simulation_t * ret = (Simulation_t *)malloc(sizeof(Simulation_t));
	ret->b0 = Vector2_fInit(0.0f,0.0f);
	ret->b1 = Vector2_fInit(x, y);
	ret->particles = Llist_fInit(NULL,NULL);

	return ret;
}
Simulation_t * Simulation_pAdd(Simulation_t * s, void * particle )
{
	Llist_Prepend(s->particles, particle);
	s->nump += 1;
	return s;
}
Simulation_t * Simulation_Rand(Simulation_t * s, int pnum)
{
	float rx,ry,rm,rr;

	int i;
	for(i = 0;i < pnum;i++)
	{
		rx = FRandomNum( -0.9f, 0.9f );
		ry = FRandomNum( -0.9f, 0.9f );
		rm = FRandomNum( 1.0f, 10.0f );
		rr = FRandomNum( 0.01, 0.02f );
		Simulation_pAdd( s, Particle_fsInit( rx, ry, rm, rr));
	}

	return s;
}

void PsCW(Simulation_t * s)
{
	Llist_t * tmp = Llist_Next(s->particles);
	Particle_t * p;

	int i;
// #pragma omp parallel for default(none) shared(s,tmp) private(i,p)
	for(i=0;i<s->nump;i++)
	{
		p = Llist_Data(tmp);
		if(p->pos->x + p->r > s->b1->x)
		{
			p->pos->x = s->b1->x - p->r;
		}
		else if(p->pos->x - p->r < s->b0->x)
		{
			p->pos->x = s->b0->x + p->r;
		}

		if(p->pos->y + p->r > s->b1->y)
		{
			p->pos->y = s->b1->y - p->r;
		}
		else if(p->pos->y - p->r < s->b0->y)
		{
			p->pos->y = s->b0->y + p->r;
		}

		tmp = Llist_Next(tmp);

	}
	/*while(tmp)
	{
		p = Llist_Data(tmp);
		if(p->pos->x + p->r > s->b1->x)
		{
			p->pos->x = s->b1->x - p->r;
		}
		else if(p->pos->x - p->r < s->b0->x)
		{
			p->pos->x = s->b0->x + p->r;
		}

		if(p->pos->y + p->r > s->b1->y)
		{
			p->pos->y = s->b1->y - p->r;
		}
		else if(p->pos->y - p->r < s->b0->y)
		{
			p->pos->y = s->b0->y + p->r;
		}

		tmp = Llist_Next(tmp);
	}*/
}

void PsCPs(Simulation_t * s)
{

	Particle_t * p1, * p2;
	Vector2_t dx;
	float l, pu;

	Llist_t * tmp1 = Llist_Next(s->particles), * tmp2;

	int i,j;
    //    #pragma omp parallel for default(none) shared(s) private(tmp1,tmp2,i,dx,p1,p2,l,pu)
	for(i=0;i<s->nump;i++)
//	while(tmp1)
	{
		p1 = Llist_Data(tmp1);

		tmp2 = Llist_Next(tmp1);
        //#pragma omp parallel for default(none) shared(p1) private(j,p2,l,pu)
		//for(j=i; j < s->nump; i++)
        while(tmp2)
		{
			p2 = Llist_Data(tmp2);


			dx.x = p2->pos->x - p1->pos->x;
			dx.y = p2->pos->y - p1->pos->y;
			l = Vector2_Len(&dx) - p1->r - p2->r;

			if(l < 0)
			{

				Vector2_Norma(&dx);
				pu = l / (p1->m + p2->m);
                pu *= 0.4;

				p1->pos->x += dx.x * pu * p2->m;
				p1->pos->y += dx.y * pu * p2->m;

				p2->pos->x -= dx.x * pu * p1->m;
				p2->pos->y -= dx.y * pu * p1->m;

			}


			tmp2 = Llist_Next(tmp2);
		}

		tmp1 = Llist_Next(tmp1);
	}

}


Simulation_t * Simulation_Upd(Simulation_t * s, float dt)
{
	Llist_t * tmp = Llist_Next(s->particles);
	Particle_t * p;
	float vx,vy;

	/*while(tmp)
	{
		p = Llist_Data(tmp);
		vx = (p->pos->x - p->oldpos->x)*0.999f;
		vy = (p->pos->y - p->oldpos->y)*0.999f;
		if(sqrt(vx*vx)<0.0001f)vx=0.0f;
		if(sqrt(vy*vy)<0.0001f)vy=0.0f;
		p->oldpos->x = p->pos->x;
		p->oldpos->y = p->pos->y;
		p->pos->x += vx;
		p->pos->y += vy;
		tmp = Llist_Next(tmp);
	}*/
	int i;
    //    #pragma omp parallel for default(none) shared(s,tmp) private(i,p,vx,vy)
	for(i = 0; i < s->nump; i++)
	{
		p = Llist_Data(tmp);

		vx = (p->pos->x - p->oldpos->x)*0.999f;
		vy = (p->pos->y - p->oldpos->y)*0.999f;
		///if(sqrt(vx*vx)<0.0001f)vx=0.0f;
		//if(sqrt(vy*vy)<0.0001f)vy=0.0f;
		p->oldpos->x = p->pos->x;
		p->oldpos->y = p->pos->y;
		p->pos->x += vx;
		p->pos->y += vy - 0.00005;


		tmp = Llist_Next(tmp);
	}

	PsCPs(s);
	PsCW(s);

	return s;
}

