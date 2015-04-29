#ifndef __MY_TIME__
#define __MY_TIME__

#include <sys/time.h>

typedef struct
{
	struct timeval last;
}				Time;

Time	*Time_new();
void	Time_delete(Time *this);
Time	*Time_init(Time	*this);

float	Time_update(Time *this);
float	Time_elapsed(Time *this);

void	Time_sleep(float t);

#endif