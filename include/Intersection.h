#ifndef __INTERSECTION__
#define __INTERSECTION__

#include "Vec3.h"
#include "Color.h"

struct sMaterial;

typedef struct
{
	float				hitDistance;
	Vec3				position;
	Vec3				normal;
	struct sMaterial	*material;
	Color				shade;
}						Intersection;

Intersection	*Intersection_new();
void			Intersection_delete(Intersection *this);
Intersection	*Intersection_init(Intersection *this);

#endif