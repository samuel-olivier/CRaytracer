#ifndef __RAY__
#define __RAY__

#include "Vec3.h"

typedef enum
{
	Primary,
	Shadow,
	Reflected
}			RayType;

typedef struct
{
	Vec3	*position;
	Vec3	*direction;
	RayType	type;
}			Ray;

Ray		*Ray_new(Vec3 *position, Vec3 *direction, RayType type);
void	Ray_delete(Ray *this);

#endif