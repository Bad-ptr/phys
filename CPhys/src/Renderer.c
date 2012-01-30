#include "Renderer.h"
#include "kmath.h"

#include <GL/glut.h>
#include <GL/glext.h>
#include <GL/glx.h>
#include <string.h>

#include "kmath.h"
#include "kshared.h"
#include "ThreadedTimer.h"


#define GLUT_KEY_ESCAPE 27



Simulation_t * sim;


void DrawColorCube(){

	glBegin(GL_QUAD_STRIP);
	// glNormal3i(0,0,-1);
	glColor3f(0,1,1);glVertex3i(0,1,-1);         glColor3f(1,1,1);glVertex3i(1,1,-1);
	//                     (+)--------------------------(+)
	//                      |                            |
	//                      |                            |
	//    glColor3f(0,1,0);glVertex3i(0,1,0);  glColor3f(1,1,0);glVertex3i(1,1,0);
	//           +--------------------------+            |
	//           |          |               |            |
	//           |          |               |            |
	//           |         (+)--------------|-----------(+)
	glColor3f(0,0,1);glVertex3i(0,0,-1);        glColor3f(1,0,1);glVertex3i(1,0,-1);
	//           |                          |
	//           |                          |
	//           +--------------------------+
	//glColor3f(0,0,0);glVertex3i(0,0,0);  glColor3f(1,0,0);glVertex3i(1,0,0);
	//
	glEnd();
	glBegin(GL_QUAD_STRIP);
	//glNormal3i(0,1,0);
	glColor3f(0,1,1);glVertex3i(0,1,-1);         glColor3f(1,1,1);glVertex3i(1,1,-1);
	//              (+)------------------------(+)
	//              /                          /
	//             /                          /
	glColor3f(0,1,0);glVertex3i(0,1,0);  glColor3f(1,1,0);glVertex3i(1,1,0);
	//          (+)------------------------(+)
	//
	//
	//               +-------------------------+
	//glColor3f(0,0,1);glVertex3i(0,0,1);     / glColor3f(1,0,1);glVertex3i(1,0,1);
	//             /                         /
	//            /                         /
	//           +-------------------------+
	//glColor3f(0,0,0);glVertex3i(0,0,0);  glColor3f(1,0,0);glVertex3i(1,0,0);
	//
	glEnd();
	glBegin(GL_QUAD_STRIP);
	//glNormal3i(1,0,0);
	/*glColor3f(0,1,1);glVertex3i(0,1,1);*/     glColor3f(1,1,1);glVertex3i(1,1,-1);
	//               +                         (+)
	//              /|                         /|
	//             / |                        / |
	/* glColor3f(0,1,0);glVertex3i(0,1,0);*/ glColor3f(1,1,0);glVertex3i(1,1,0);
	//           +   |                     (+)  |
	//           |   |                      |   |
	//           |   |                      |   |
	//           |   +                      |  (+)
	/*glColor3f(0,0,1);glVertex3i(0,0,1);*/      glColor3f(1,0,1);glVertex3i(1,0,-1);
	//           | /                        | /
	//           |/                         |/
	//           +                         (+)
	/*glColor3f(0,0,0);glVertex3i(0,0,0);*/  glColor3f(1,0,0);glVertex3i(1,0,0);
	//
	glEnd();
	glBegin(GL_QUAD_STRIP);
	//glNormal3i(1,0,0);
	glColor3f(0,1,1);glVertex3i(0,1,-1);        // glColor3f(1,1,1);glVertex3i(1,1,1);
	//                    (+)-------------------------+
	//                     |                          |
	//                     |                          |
	glColor3f(0,1,0);glVertex3i(0,1,0);  //glColor3f(1,1,0);glVertex3i(1,1,0);
	//          (+)-------------------------+
	//           |         |                |         |
	//           |         |                |         |
	//           |        (+)---------------|---------+
	glColor3f(0,0,1);glVertex3i(0,0,-1);      //glColor3f(1,0,1);glVertex3i(1,0,1);
	//           |                          |
	//           |                          |
	//          (+)-------------------------+
	glColor3f(0,0,0);glVertex3i(0,0,0);  //glColor3f(1,0,0);glVertex3i(1,0,0);
	//
	glEnd();
	glBegin(GL_QUAD_STRIP);
	//glNormal3i(1,0,0);
	/*glColor3f(0,1,1);glVertex3i(0,1,1);*/         //glColor3f(1,1,1);glVertex3i(1,1,1);
	//                     +--------------------------+
	//                     |                          |
	//                     |                          |
	/* glColor3f(0,1,0);glVertex3i(0,1,0);*/  //glColor3f(1,1,0);glVertex3i(1,1,0);
	//           +--------------------------+
	//           |         |                |         |
	//           |         |                |         |
	//           |        (+)---------------|--------(+)
	glColor3f(0,0,1);glVertex3i(0,0,-1);      glColor3f(1,0,1);glVertex3i(1,0,-1);
	//           |                          |
	//           |                          |
	//          (+)------------------------(+)
	glColor3f(0,0,0);glVertex3i(0,0,0);  glColor3f(1,0,0);glVertex3i(1,0,0);
	//
	glEnd();
	glBegin(GL_QUAD_STRIP);
	//glNormal3i(1,0,0);
	/*glColor3f(0,1,1);glVertex3i(0,1,1);*/         //glColor3f(1,1,1);glVertex3i(1,1,1);
	//                     +--------------------------+
	//                     |                          |
	//                     |                          |
	glColor3f(0,1,0);glVertex3i(0,1,0);  glColor3f(1,1,0);glVertex3i(1,1,0);
	//          (+)------------------------(+)
	//           |         |                |         |
	//           |         |                |         |
	//           |         +----------------|---------+
	//glColor3f(0,0,1);glVertex3i(0,0,1);*/      glColor3f(1,0,1);glVertex3i(1,0,1);
	//           |                          |
	//           |                          |
	//          (+)------------------------(+)
	glColor3f(0,0,0);glVertex3i(0,0,0);  glColor3f(1,0,0);glVertex3i(1,0,0);
	//
	glEnd();
}


void * Circle3D(float ox,float oy,float oz,float r, int numvert){

	float alp, k = 360/numvert;
	int i;
//	void * ret = malloc(sizeof(float)*3*numvert);
//	float (*ar)[numvert][3] = ret;
	//Listid = glGenLists(1);
	//glNewList(Listid, GL_COMPILE);
    glBegin(GL_POLYGON);
    //#pragma omp parallel for default(none)    \
    // shared(r,k,numvert,ox,oy,oz) private(i,alp)
	for(i = 0; i < numvert; i ++){
		alp = DegToRad(k*i);
/*		(*ar)[i][0] = r * (float)cos(alp) + ox;
		(*ar)[i][1] = r * (float)sin(alp) + oy;
		(*ar)[i][2] = oz;*/
		glVertex3f(r*(float)cos(alp)+ox,r*(float)sin(alp)+oy,oz);
	}
		glEnd();
	//glEndList();
	return NULL;//ret;

};


void updsim(void)
{
	//Simulation_Upd(sim,0.0f);
	//glutSwapBuffers();
	glutPostRedisplay();
}

void speckeyfunk(int key, int x, int y)
{
  switch(key)
	{
    case GLUT_KEY_RIGHT:
      ((Particle_t*)sim->particles->next->data)->pos->x += 0.0002;
      break;
      
    case GLUT_KEY_LEFT:
      ((Particle_t*)sim->particles->next->data)->pos->x -= 0.0002;
      break;
      
    case GLUT_KEY_UP:
      ((Particle_t*)sim->particles->next->data)->pos->y += 0.0002;
      break;
      
    case GLUT_KEY_DOWN:
      ((Particle_t*)sim->particles->next->data)->pos->y -= 0.0002;
      break;
      
    case GLUT_KEY_ESCAPE:
      exit(0);
      break;
      
    default:
      break;
	}
}

void Gl_Init()
{
	glClearColor(0, 0, 0, 0);
	glPolygonMode(GL_FRONT_AND_BACK, GL_SMOOTH);
	glEnable(GL_CULL_FACE);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);

	glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
	glHint(GL_POINT_SMOOTH_HINT, GL_NICEST);
	glHint(GL_POLYGON_SMOOTH_HINT, GL_NICEST);
	glHint(GL_LIGHTING, GL_NICEST);
	glEnable(GL_LINE_SMOOTH);
	glEnable(GL_POINT_SMOOTH);
	glEnable(GL_POLYGON_SMOOTH);

	glColorMaterial(GL_FRONT, GL_DIFFUSE| GL_SPECULAR);
	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	//glEnable(GL_STENCIL_TEST);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	//gluPerspective(90,1,0.1,100);
	glOrtho( 0, 800 , 0 , 600, 0.1, 100 );
	//gluLookAt(0, 0, 0.1, 0.0, 0.0, 0, 0, 1, 0);
	//glMatrixMode(GL_PROJECTION);
	//glPushMatrix();
	//glLoadIdentity();
	//glOrtho( 0, 800 , 0 , 600, 0.1, 100 );
	//gluLookAt(0,0,0.1,0.0,0.0,0,0,1,0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

/*	float circle3d[] = {
			-0.8f, -0.8f, -1.0f,
			 0.0f,  0.8f, -1.0f,
			 0.8f, -0.8f, -1.0f
		};//Circle3D(0,0,-1.0f, 0.5f, 100);
	VBOid = makeVBO(circle3d,sizeof(float)*3*3);
	makeShaderprog("shader");*/

	sim = Simulation_wflsInit(1.0f,1.0f);
	sim->b0->x = -1.0f;
	sim->b0->y = -1.0f;
	//Simulation_Rand(sim,1);
	Simulation_Rand(sim,3000);
	Simulation_pAdd(sim,Particle_fsInit(0.0f,0.0f,1000,0.05));
	//Circle3D(0.0f,0.0f,-1.0f,1.0f,10);

	ThreadedTimer_t *TTimer = ThreadedTimer_fInit(100000,(timer_func_t)Simulation_Upd,sim);
	ThreadedTimer_Start(TTimer);
};


void DrawScene(void)
{
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

/*	glLineWidth(1);
	glColor3f(1,0,0);
	glBegin(GL_LINE_STRIP);
	float i = 0.0f;
	for(i=0.0f;i<1001;i+=0.001f){
		glVertex3f((i-1)*0.01,sin(i)-1,-1);
	}
	glEnd();

	//glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glRotatef(50,0.4,0.7,0.1);
	DrawColorCube();
	glPopMatrix();*/
	//glRotatef(10,0.5,0.5,0.5);
    glColor4f(0.4f,0.0f,0.0f,1.0f);

	Llist_t * tmp = Llist_Next(sim->particles);
	Particle_t *p;
	//glBegin(GL_POINTS);
	while(tmp)
	{
		p = Llist_Data(tmp);
		Circle3D(p->pos->x,p->pos->y,-1.0,p->r,10);
		tmp = Llist_Next(tmp);
	}
	//glEnd();

	//glFlush();
    //glFinish();
	glutSwapBuffers();
};

void ResizeScene(int x, int y)
{
  glutReshapeWindow(800,600);
	//glMatrixMode(GL_PROJECTION);
	//glLoadIdentity();
	//gluPerspective(90,1,0.1,100);
	//gluLookAt(0,0,0.1,0.0,0.0,0,0,1,0);*/
  glViewport(0,0,x,y);
	//glMatrixMode(GL_PROJECTION);
	//glPushMatrix();
	//glLoadIdentity();
	//glOrtho( 0, 800 , 0 , 600, 0.1, 100 );
//	glMatrixMode(GL_MODELVIEW);
	//glPushMatrix();
//	glLoadIdentity();
};

Renderer_t * Renderer_new(Renderer_t * r)
{
	Renderer_t * ret = (Renderer_t*)malloc(sizeof(Renderer_t));

	if(r)
	{
		ret->x0 = r->x0;
		ret->y0 = r->y0;
		ret->x = r->x;
		ret->y = r->y;
		ret->header = r->header;
		ret->render_func = r->render_func;
		ret->resize_func = r->resize_func;
		ret->idle_func = r->idle_func;

	}
	else
	{
		ret->x0 = 0.0f;
		ret->y0 = 0.0f;
		ret->x = 800.0f;
		ret->y = 600.0f;
		ret->header = "K";
		ret->render_func = DrawScene;
		ret->resize_func = ResizeScene;
		ret->idle_func = NULL;
	}


	return ret;

};

Renderer_t * Renderer_Init(Renderer_t * r, int argc, char * argv[],
	float x0, float y0, float x, float y, char * header,
	void(*rf)(void), void(*resf)(int,int), void(*idlef)(void) )
{
	if(!r)
		r = Renderer_new(r);

	r->x0 = x0;
	r->y0 = y0;
	r->x = x;
	r->y = y;
	r->header = header;

	r->render_func = rf;
	if ( !r->render_func )
		r->render_func = DrawScene;

	r->resize_func = resf;
	if ( !r->resize_func )
		r->resize_func = ResizeScene;

	r->idle_func = idlef;
	if ( !r->idle_func )
		r->idle_func = updsim;

    glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH|GLUT_DOUBLE);
	glutInitWindowSize(r->x,r->y);
	glutInitWindowPosition(r->x0,r->y0);
	Gl_Init();

	return r;
};

Renderer_t * Renderer_Start(Renderer_t * r)
{
  if(!r)
    return NULL;

  glutCreateWindow(r->header);
  glutDisplayFunc(r->render_func);
  glutReshapeFunc(r->resize_func);
  glutIdleFunc(r->idle_func);
  glutSpecialFunc(speckeyfunk);
  glutMainLoop();
  
  return r;
};

