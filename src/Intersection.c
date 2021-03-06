#include "Intersection.h"

#include <stdlib.h>

Intersection	*Intersection_new()
{
	return Intersection_init(malloc(sizeof(Intersection)));
}

void			Intersection_delete(Intersection *this)
{
	free(this);
}

Intersection	*Intersection_init(Intersection *this)
{
	this->hitDistance = 1e10f;
	Vec3_init(&this->position);
	Vec3_init(&this->normal);
	Vec3_init(&this->u);
	Vec3_init(&this->v);
	this->material = NULL;
	this->object = NULL;
	Color_init(&this->shade);
	return this;
}
