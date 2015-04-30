#include "Sphere.h"

#include <stdlib.h>
#include <math.h>

#include "Config.h"

static void		Sphere_deleteObject(void *this);

Object	*Sphere_new(Vec3 *position, float radius)
{
	Sphere	*data = malloc(sizeof(*data));
	data->position = *position;
	data->radius = radius;

	Object	*this = Object_new();
	this->data = data;
	this->intersectPtr = &Sphere_intersect;
	this->deletePtr = &Sphere_deleteObject;
	return this;
}

void	Sphere_delete(Sphere *this)
{
	free(this);
}

int		Sphere_intersect(Object *this, Ray *ray, Intersection *hit)
{
	Sphere	*sphere = this->data;
	Vec3	sphereRay;
	Vec3_subVectors(&sphereRay, &ray->origin, &sphere->position);
	float	t = -Vec3_dot(&sphereRay, &ray->direction);
	Vec3	q;
	Vec3_addScaledVectors(&q, &ray->origin, &ray->direction, t);
	Vec3	qOrigin;
	Vec3_subVectors(&qOrigin, &q, &sphere->position);
	float aSquared = sphere->radius * sphere->radius - Vec3_lengthSquared(&qOrigin);
	if (aSquared < 0) {
	    return 0;
	}
	float a = sqrt(aSquared);

	float dist;
	if (t - a > 0) {
		dist = t - a;
	} else if (t + a > 0) {
		dist = t + a;
	} else {
		return 0;
	}
	if (dist > EPSILON && dist < hit->hitDistance) {
		if (ray->type == ShadowRay) {
			return 1;
		}
		hit->hitDistance = dist;
		Vec3_addScaledVectors(&hit->position, &ray->origin, &ray->direction, dist);
		hit->material = this->material;
		hit->object = this;
		Vec3_subVectors(&hit->normal, &hit->position, &sphere->position);
		Vec3_normalize(&hit->normal);
		Vec3	up;
		Vec3_setValues(&up, 0.f, 1.f, 0.f);
		Vec3_crossVectors(&hit->u, &up, &hit->normal);
		if (Vec3_lengthSquared(&hit->u) < EPSILON) {
			Vec3_setValues(&hit->u, 1.f, 0.f, 0.f);
		} else {
			Vec3_normalize(&hit->u);
		}
		Vec3_crossVectors(&hit->v, &hit->normal, &hit->u);
		return 1;
	}
	return 0;
}

static void	Sphere_deleteObject(void *this)
{
	Sphere_delete(this);
}
