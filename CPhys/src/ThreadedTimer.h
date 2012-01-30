#include "Thread.h"

typedef void* (*timer_func_t)(void*,unsigned long);
#define TIMERF(f) ((timer_func_t)f)

typedef struct ThreadedTimer_s
{
	unsigned long period;
	timer_func_t timer_func;
	void* arg;
	Thread_t* thread;

} ThreadedTimer_t;


unsigned long ThreadedTimer_getperiod(ThreadedTimer_t *T);
void ThreadedTimer_setperiod(ThreadedTimer_t *T,unsigned long period);

timer_func_t ThreadedTimer_gettimer_func(ThreadedTimer_t *T);
//void ThreadedTimer_settimer_func(ThreadedTimer_t *T,void* timer_func);

void* ThreadedTimer_getarg(ThreadedTimer_t *T);
//void ThreadedTimer_setarg(ThreadedTimer_t *T,void* arg);

Thread_t* ThreadedTimer_getthread(ThreadedTimer_t *T);
//void ThreadedTimer_setthread(ThreadedTimer_t *T,Thread_t* thread);

ThreadedTimer_t * ThreadedTimer_new(ThreadedTimer_t *T);
ThreadedTimer_t * ThreadedTimer_Init(ThreadedTimer_t *T, unsigned long period,
		timer_func_t timer_func, void* arg);
ThreadedTimer_t * ThreadedTimer_fInit(unsigned long period,
		timer_func_t timer_func, void* arg);

int ThreadedTimer_Start(ThreadedTimer_t *T);
int ThreadedTimer_Stop(ThreadedTimer_t *T);

void* ThreadedTimer_Cleanup(ThreadedTimer_t *T);
void* ThreadedTimer_Destroy(ThreadedTimer_t *T);
