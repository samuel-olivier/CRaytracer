#ifndef __INTERSECTION__
#define __INTERSECTION__

#include "Vec3.h"
#include "Color.h"

struct sMaterial;
struct sObject;

typedef struct
{
	float				hitDistance;
	Vec3				position;
	Vec3				normal;
	Vec3				u;
	Vec3				v;
	struct sMaterial	*material;
	Color				shade;
	struct sObject			*object;
}						Intersection;

Intersection	*Intersection_new();
void			Intersection_delete(Intersection *this);
Intersection	*Intersection_init(Intersection *this);

#endif
