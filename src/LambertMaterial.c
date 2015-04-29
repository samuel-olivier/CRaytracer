#include "LambertMaterial.h"

#include <stdlib.h>
#include <math.h>

#include "Utils.h"

static void		LambertMaterial_deleteMaterial(void *this);

Material	*LambertMaterial_new(Color *diffuseColor)
{
	LambertMaterial	*data = malloc(sizeof(*data));
	data->diffuseColor = *diffuseColor;

	Material	*this = Material_new();
	this->data = data;
	this->computePtr = &LambertMaterial_computeReflectance;
	this->samplePtr = &LambertMaterial_sampleRay;
	this->deletePtr = &LambertMaterial_deleteMaterial;
	return this;
}

void		LambertMaterial_delete(LambertMaterial *this)
{
	free(this);
}

void	LambertMaterial_computeReflectance(Material *this, Color *col, Vec3 *in, Ray *ray, Intersection *hit)
{
	LambertMaterial	*lambert = this->data;

	*col = lambert->diffuseColor;
	Color_scale(col, 1.0f / M_PI);
	(void)in;
	(void)ray;
	(void)hit;
}

int		LambertMaterial_sampleRay(Material *this, Ray *ray, Intersection *hit, Ray *newRay, Color *intensity)
{
	LambertMaterial	*lambert = this->data;
	float s = (float)rand() / RAND_MAX;
	float t = (float)rand() / RAND_MAX;
	float u = 2.0f * M_PI * s;
	float v = sqrtf(1.f - t);

	newRay->origin = hit->position;
	Vec3_scaleVector(&newRay->direction, &hit->normal, sqrtf(t));
	Vec3_addScaled(&newRay->direction, &hit->u, v * cosf(u));
	Vec3_addScaled(&newRay->direction, &hit->v, v * sinf(u));
	*intensity = lambert->diffuseColor;
	newRay->type = DiffusedRay;
	return 1;
	(void)ray;
}

static void		LambertMaterial_deleteMaterial(void *this)
{
	LambertMaterial_delete(this);
}