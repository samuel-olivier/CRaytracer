#ifndef __INTERSECTION__
#define __INTERSECTION__

#include "Material.h"
#include "Vec3.h"
#include "Color.h"

typedef struct
{
	float		hitDistance;
	Vec3		position;
	Vec3		normal;
	Material	*material;
	Color		shade;
}				Intersection;

Intersection	*Intersection_new();
void			Intersection_delete(Intersection *this);
Intersection	*Intersection_init(Intersection *this);

#endif