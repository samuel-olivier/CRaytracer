#define _POSIX_C_SOURCE 199309L

#include "Time.h"

#include <stdlib.h>
#include <strings.h>
#include <time.h>

static float	elapsed(Time *this, struct timeval *now);

Time	*Time_new()
{
	return Time_init(malloc(sizeof(Time)));
}

void	Time_delete(Time *this)
{
	free(this);
}

Time	*Time_init(Time	*this)
{
	bzero(&this->last, sizeof(this->last));
	Time_update(this);
	return this;
}

float	Time_update(Time *this)
{
	struct timeval	now;
	float			res = elapsed(this, &now);

	this->last = now;
	return res;
}

float	Time_elapsed(Time *this)
{
	struct timeval	now;

	return elapsed(this, &now);
}

void	Time_sleep(float t)
{
	struct timespec s;

	s.tv_sec = t;
	s.tv_nsec = (t - (int)t) * 10e8;
	nanosleep(&s, NULL);
}

static float	elapsed(Time *this, struct timeval *now)
{
	gettimeofday(now, NULL);
	return now->tv_sec - this->last.tv_sec + ((float)(now->tv_usec - this->last.tv_usec) / 1000000.f);
}