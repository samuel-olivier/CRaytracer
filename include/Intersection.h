#ifndef __INTERSECTION__
#define __INTERSECTION__

typedef struct
{
	float		hitDistance;
	Vec3		position;
	Vec3		normal;
	Material	*material;
	Color		shade;
}				Intersection;

#endif