#ifndef __TRIANGLE__
#define __TRIANGLE__

#include "Vertex.h"
#include "Object.h"
#include "Vec3.h"

typedef struct
{
	Vertex		*v0;
	Vertex		*v1;
	Vertex		*v2;
	Vec3		normal;
}				Triangle;

Object	*Triangle_new(Vertex *v0, Vertex *v1, Vertex *v2);
void	Triangle_delete(Triangle *this);

int		Triangle_intersect(Object *this, Ray *ray, Intersection *hit);

#endif