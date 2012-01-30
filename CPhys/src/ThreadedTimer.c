#include <stdlib.h>
#include <sys/time.h>

#include "ThreadedTimer.h"

unsigned long ThreadedTimer_getperiod(ThreadedTimer_t *T)
{
	return T->period;
}
void ThreadedTimer_setperiod(ThreadedTimer_t *T,unsigned long period)
{
	T->period = period;
}

timer_func_t ThreadedTimer_gettimer_func(ThreadedTimer_t *T)
{
	return T->timer_func;
}
void ThreadedTimer_settimer_func(ThreadedTimer_t *T,timer_func_t timer_func)
{
	T->timer_func = timer_func;
}

void* ThreadedTimer_getarg(ThreadedTimer_t *T)
{
	return T->arg;
}
void ThreadedTimer_setarg(ThreadedTimer_t *T,void* arg)
{
	T->arg = arg;
}

Thread_t* ThreadedTimer_getthread(ThreadedTimer_t *T)
{
	return T->thread;
}
void ThreadedTimer_setthread(ThreadedTimer_t *T,Thread_t* thread)
{
	T->thread = thread;
}



void* TimerLoop(ThreadedTimer_t *T)
{
	unsigned long dt = 0;
	struct timeval ctv;

	while(1)
	{
		gettimeofday(&ctv,NULL);
        
		dt += ctv.tv_usec;

		if ( dt >= T->period )
		{
			dt = 0;
			T->timer_func(T->arg, dt);
		}

	}

	return NULL;
}




ThreadedTimer_t * ThreadedTimer_new(ThreadedTimer_t *T)
{
	ThreadedTimer_t *ret = malloc(sizeof(ThreadedTimer_t));
	if(!T)
	{
		ret->period = 0;
		ret->timer_func = NULL;
		ret->arg = NULL;
		ret->thread = NULL;
	}
	else
	{
		ret->period = T->period;
		ret->timer_func = T->timer_func;
		ret->arg = T->arg;
		ret->thread = T->thread;
	}

	return ret;
}

ThreadedTimer_t * ThreadedTimer_Init(ThreadedTimer_t *T, unsigned long period,
		timer_func_t timer_func, void* arg)
{
	if(!T)
		T = malloc(sizeof(ThreadedTimer_t));

	T->period = period;
	T->timer_func = timer_func;
	T->arg = arg;
	T->thread = NULL;

	return T;
}
ThreadedTimer_t * ThreadedTimer_fInit(unsigned long period,
		timer_func_t timer_func, void* arg)
{
	ThreadedTimer_t *T = malloc(sizeof(ThreadedTimer_t));

	T->period = period;
	T->timer_func = timer_func;
	T->arg = arg;
	T->thread = Thread_fInit(NULL,(pthread_func_t)TimerLoop,T);

	return T;
}



int ThreadedTimer_Start(ThreadedTimer_t *T)
{

	Thread_Start(T->thread);
    return 0;

}
int ThreadedTimer_Stop(ThreadedTimer_t *T)
{

	Thread_Stop(T->thread);
    return 0;

}


void* ThreadedTimer_Cleanup(ThreadedTimer_t *T)
{
	return NULL;
}
void* ThreadedTimer_Destroy(ThreadedTimer_t *T)
{
	Thread_Destroy(T->thread);
	free(T);
	return NULL;
}
