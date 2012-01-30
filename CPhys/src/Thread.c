#include <stdlib.h>
#include "Thread.h"

pthread_t Thread_getid(Thread_t *T)
{
	return T->id;
}
void Thread_setid(Thread_t *T,pthread_t i)
{
	T->id = i;
}

void* Thread_getattr(Thread_t *T)
{
	return T->attr;
}
void Thread_setattr(Thread_t *T,void* a)
{
	T->attr = a;
}

unsigned int Thread_getcondition(Thread_t *T)
{
	return T->condition;
}
void Thread_setcondition(Thread_t *T,unsigned int c)
{
	T->condition = c;
}

pthread_func_t Thread_getthread_func(Thread_t *T)
{
	return T->thread_func;
}
void Thread_setthread_func(Thread_t *T,pthread_func_t t)
{
	T->thread_func = t;
}

void* Thread_getarg(Thread_t *T)
{
	return T->arg;
}
void Thread_setarg(Thread_t *T,void* a)
{
	T->arg = a;
}

Thread_t * Thread_new(Thread_t *T)
{
	Thread_t *ret = malloc(sizeof(Thread_t));
	if(!T)
	{
		ret->id = 0;
		ret->attr = NULL;
		ret->condition = 0;
		ret->thread_func = NULL;
		ret->arg = NULL;
	}
	else
	{
		ret->id = 0;
		ret->attr = T->attr;
		ret->condition = 0;
		ret->thread_func = T->thread_func;
		ret->arg = T->arg;
	}

	return ret;
}

Thread_t * Thread_Init(Thread_t *T, void* attr, pthread_func_t thread_func, void* arg)
{
	if(!T)
		T = malloc(sizeof(Thread_t));

	T->id = 0;
	T->attr = attr;
	T->condition = 0;
	T->thread_func = thread_func;
	T->arg = arg;

	return T;
}
Thread_t * Thread_fInit(void* attr, pthread_func_t thread_func, void* arg)
{
	Thread_t *T = malloc(sizeof(Thread_t));

    if( NULL == attr)
      {
        attr = malloc( sizeof( pthread_attr_t ) );
        pthread_attr_init( attr );
        pthread_attr_setdetachstate(attr, PTHREAD_CREATE_DETACHED);
      }

	T->id = 0;
	T->attr = attr;
	T->condition = 0;
	T->thread_func = thread_func;
	T->arg = arg;

	return T;
}


int Thread_Start(Thread_t *T)
{
	T->condition = 1;
	return pthread_create( &T->id, T->attr, T->thread_func, T->arg);
}
int Thread_Stop(Thread_t *T)
{
	T->condition = 0;
	return pthread_cancel(T->id);
}

void* Thread_Cleanup(Thread_t *T)
{
	return NULL;
}
void* Thread_Destroy(Thread_t *T)
{
	Thread_Stop(T);
	free(T);
	return NULL;
}
