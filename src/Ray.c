#include "Ray.h"

#include <stdlib.h>

Ray		*Ray_new(Vec3 *origin, Vec3 *direction, RayType type)
{
	return Ray_init(malloc(sizeof(Ray)), origin, direction, type);
}

void	Ray_delete(Ray *this)
{
	free(this);
}

Ray		*Ray_init(Ray *this, Vec3 *origin, Vec3 *direction, RayType type)
{
	this->origin = *origin;
	this->direction = *direction;
	this->type = type;
	return this;
}
