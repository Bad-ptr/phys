#include <pthread.h>

typedef void* (*pthread_func_t)(void*);

typedef struct Thread_s
{
	pthread_t id;
	void* attr;
	unsigned int condition;
	pthread_func_t thread_func;
	void* arg;
} Thread_t;


pthread_t Thread_getid(Thread_t *T);
//void Thread_setid(Thread_t *T,pthread_t i);

void* Thread_getattr(Thread_t *T);
void Thread_setattr(Thread_t *T,void* attr);

unsigned int Thread_getcondition(Thread_t *T);
//void Thread_setcondition(Thread_t *T,unsigned int c);

pthread_func_t Thread_getthread_func(Thread_t *T);
//void Thread_setthread_func(Thread_t *T,void* t);

void* Thread_getarg(Thread_t *T);
//void Thread_setarg(Thread_t *T,void* a);

Thread_t * Thread_new(Thread_t *T);
Thread_t * Thread_Init(Thread_t *T, void* attr, pthread_func_t thread_func, void* arg);
Thread_t * Thread_fInit(void* attr, pthread_func_t thread_func, void* arg);

int Thread_Start(Thread_t *T);
int Thread_Stop(Thread_t *T);

void* Thread_Cleanup(Thread_t *T);
void* Thread_Destroy(Thread_t *T);
