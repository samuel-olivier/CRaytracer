#include "Triangle.h"

#include <stdlib.h>

#include "Config.h"

static void	Triangle_deleteObject(void *this);

Object	*Triangle_new(Vertex *v0, Vertex *v1, Vertex *v2)
{
	Triangle	*data = malloc(sizeof(*data));
	data->v0 = v0;
	data->v1 = v1;
	data->v2 = v2;

	Object		*this = Object_new();
	this->data = data;
	this->intersectPtr = &Triangle_intersect;
	this->deletePtr = &Triangle_deleteObject;	
	return this;
}

void		Triangle_delete(Triangle *this)
{
	free(this);
}

int			Triangle_intersect(Object *this, Ray *ray, Intersection *hit)
{
	Triangle	*triangle = this->data;

	if (!triangle->v0 || !triangle->v1 || !triangle->v2) {
		return 0;
	}
	Vec3	a;
	Vec3_subVectors(&a, &triangle->v1->position, &triangle->v0->position);
	Vec3	b;
	Vec3_subVectors(&b, &triangle->v2->position, &triangle->v0->position);
	Vec3	crossAB;
	Vec3_crossVectors(&crossAB, &a, &b);
	float	detM = -Vec3_dot(&ray->direction, &crossAB);
	if (detM == 0.f) {
		return 0;
	}
	Vec3	rayV0;
	Vec3_subVectors(&rayV0, &ray->origin, &triangle->v0->position);
	Vec3	crossRayB;
	Vec3_crossVectors(&crossRayB, &rayV0, &b);
	float alpha = -Vec3_dot(&ray->direction, &crossRayB) / detM;
	if (alpha < 0.f || alpha > 1.f) {
		return 0;
	}
	Vec3	crossARay;
	Vec3_crossVectors(&crossARay, &a, &rayV0);
	float beta = -Vec3_dot(&ray->direction, &crossARay) / detM;
	if (beta < 0.f || alpha + beta > 1.f) {
		return 0;
	}
	float t = Vec3_dot(&rayV0, &crossAB) / detM;
	if (t > EPSILON && t < hit->hitDistance - EPSILON) {
		if (ray->type == ShadowRay) {
			return 1;
		}
		hit->hitDistance = t;
		Vec3_init(&hit->normal);
		Vec3_addScaled(&hit->normal, &triangle->v0->normal, (1.f - alpha - beta));
		Vec3_addScaled(&hit->normal, &triangle->v1->normal, alpha);
		Vec3_addScaled(&hit->normal, &triangle->v2->normal, beta);
		hit->material = this->material;
		Vec3_addScaledVectors(&hit->position, &ray->origin, &ray->direction, t);
		return 1;
	}
	return 0;
}

static void	Triangle_deleteObject(void *this)
{
	Triangle_delete(this);
}
