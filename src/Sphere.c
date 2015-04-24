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
		Vec3_subVectors(&hit->normal, &hit->position, &sphere->position);
		// printf("Intersect %f %f,%f,%f %f\n", dist, ray->direction.x, ray->direction.y, ray->direction.z, sphere->radius);
		return 1;
	}
	return 0;
}

static void	Sphere_deleteObject(void *this)
{
	Sphere_delete(this);
}