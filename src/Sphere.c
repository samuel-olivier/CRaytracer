#include "Sphere.h"

#include <stdlib.h>

static void		Sphere_deleteObject(void *this);

Object	*Sphere_new(Vec3 *position, float radius)
{
	Sphere	*data = malloc(sizeof(*data));
	data->position = Vec3_clone(position);
	data->radius = radius;

	Object	*this = Object_new();
	this->data = data;
	this->intersectPtr = &Sphere_intersect;
	this->deletePtr = &Sphere_deleteObject;
	return this;
}

void	Sphere_delete(Sphere *this)
{
	free(this->position);
	free(this);
}

int		Sphere_intersect(Object *this, Ray *ray, Intersection *hit)
{
	Sphere	*sphere = this->data;
	(void)sphere;
	(void)ray;
	(void)hit;
	return 0;
}

static void	Sphere_deleteObject(void *this)
{
	Sphere_delete(this);
}