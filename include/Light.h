#ifndef __LIGHT__
#define __LIGHT__

#include "Color.h"
#include "Vec3.h"
#include "Intersection.h"
#include "Ray.h"

struct sLight;

typedef float	(*Light_IlluminateFunc)(struct sLight *this, Vec3 *pos, Color *col, Vec3 *toLight, Vec3 *ltPos);
typedef void	(*Light_DeleteFunc)(void *this);


typedef struct						sLight
{
	void					*data;

	Light_IlluminateFunc	illuminatePtr;
	Light_DeleteFunc		deletePtr;
}							Light;

Light	*Light_new();
void	Light_delete(Light *this);
Light	*Light_init(Light *this);

float	Light_illuminate(Light *this, Vec3 *pos, Color *col, Vec3 *toLight, Vec3 *ltPos);

#endif