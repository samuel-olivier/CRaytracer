#include "Instance.h"

#include <stdlib.h>

static void	Instance_deleteObject(void *this);

Object	*Instance_new(Object *obj)
{
	Instance	*data = malloc(sizeof(*data));
	data->object = obj;
	Mat4x4_toIdentity(&data->m);
	Mat4x4_toIdentity(&data->mInv);
	Object		*this = Object_new();
	this->data = data;
	this->intersectPtr = &Instance_intersect;
	this->deletePtr = &Instance_deleteObject;	
	return this;
}

void	Instance_delete(Instance *this)
{
	free(this);
}

int		Instance_intersect(Object *this, Ray *ray, Intersection *hit)
{
	Instance	*instance = this->data;
	if (instance->object) {
		Vec3 invOrigin;
		Vec3 invDirection;
		Mat4x4_mapVec3(&instance->mInv, &ray->origin, &invOrigin, 1.f);
		Mat4x4_mapVec3(&instance->mInv, &ray->direction, &invDirection, 0.f);
		Ray ray2;
		Ray_init(&ray2, &invOrigin, &invDirection, ray->type);
		if (!Object_intersect(instance->object, &ray2, hit)) {
			return 0;
		}
		if (ray->type == ShadowRay) {
			return 1;
		}
		Mat4x4_mapVec3(&instance->m, &hit->position, &hit->position, 1.f);
		Mat4x4_mapVec3(&instance->m, &hit->normal, &hit->normal, 0.f);
		Vec3_normalize(&hit->normal);
		hit->hitDistance = Vec3_distanceTo(&ray->origin, &hit->position);
		if (this->material) {
			hit->material = this->material;
		}
		return 1;
	}
	return 0;
}

void	Instance_setMatrix(Object *this, Mat4x4 *m)
{
	Instance	*instance = this->data;

	instance->m = *m;
	Mat4x4_invertMatrix(&instance->mInv, &instance->m);
}

static void	Instance_deleteObject(void *this)
{
	Instance_delete(this);
}
