#ifndef __SPHERE__
#define __SPHERE__

#include "Object.h"
#include "Vec3.h"

typedef struct
{
	Vec3		*position;
	float		radius;
}				Sphere;

Object	*Sphere_new(Vec3 *position, float radius);
void	Sphere_delete(Sphere *this);

int		Sphere_intersect(Object *this, Ray *ray, Intersection *hit);

#endif