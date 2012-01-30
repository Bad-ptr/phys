#ifndef RENDERER_H_
#define RENDERER_H_

#include <GL/glut.h>

#include "Simulation.h"
#include "Particle.h"


typedef struct Renderer_s
{
	float x0, y0;
	float x, y;
	char * header;
	void (*render_func)(void);
	void (*resize_func)(int,int);
	void (*idle_func)(void);

} Renderer_t;

Renderer_t * Renderer_new(Renderer_t * r);

Renderer_t * Renderer_Init( Renderer_t * r, int argc, char * argv[],
                            float x0, float y0, float x, float y, char * header,
                            void(*rf)(void), void(*resf)(int,int), void(*idlef)(void) );

Renderer_t * Renderer_Start(Renderer_t * r);



#endif










