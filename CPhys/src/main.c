#include <stdio.h>

#include "Renderer.h"
#include "Simulation.h"


int main(int argc, char ** argv)
{
	Renderer_t * krenderer;
	krenderer = Renderer_Init(NULL,argc,argv,10,10,800,600,"3aroJloBoK",
                              NULL,NULL,NULL);

    Renderer_Start(krenderer);
    
	return(0);
}

