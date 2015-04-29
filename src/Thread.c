#include "Thread.h"

#include <stdlib.h>

typedef struct
{
	Thread_routine	routine;
	void			*data;
}					ThreadParam;

static void	*threadRoutine(void *data);

Thread		*Thread_new()
{
	return Thread_init(malloc(sizeof(Thread)));
}

void		Thread_delete(Thread *this)
{
	free(this);
}

Thread		*Thread_init(Thread *this)
{
	this->id = 0;
	return this;
}

int			Thread_run(Thread *this, Thread_routine func, void *params)
{
	ThreadParam *p = malloc(sizeof(*p));

	p->routine = func;
	p->data = params;
	return pthread_create(&this->id, NULL, threadRoutine, p);
}

int			Thread_join(Thread *this)
{
	return pthread_join(this->id, NULL);
}

static void	*threadRoutine(void *data)
{
	ThreadParam *p = data;

	p->routine(p->data);
	free(p);
	return NULL;
}