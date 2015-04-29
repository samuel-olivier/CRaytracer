#ifndef __THREAD__
#define __THREAD__

#include <pthread.h>

typedef struct
{
	pthread_t	id;
}				Thread;

typedef void	(*Thread_routine)(void *params);

Thread		*Thread_new();
void		Thread_delete(Thread *this);
Thread		*Thread_init(Thread *this);

int			Thread_run(Thread *this, Thread_routine func, void *params);
int			Thread_join(Thread *this);

#endif