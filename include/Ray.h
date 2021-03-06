#ifndef __RAY__
#define __RAY__

#include "Vec3.h"

typedef enum
{
	PrimaryRay,
	ShadowRay,
	ReflectedRay,
	TransmittedRay,
	DiffusedRay,
	RayNone
}			RayType;

typedef struct
{
	Vec3	origin;
	Vec3	direction;
	RayType	type;
	int		depth;
	float	refraction;
}			Ray;

Ray		*Ray_new(Vec3 *origin, Vec3 *direction, RayType type);
void	Ray_delete(Ray *this);
Ray		*Ray_init(Ray *this, Vec3 *origin, Vec3 *direction, RayType type);

#endif