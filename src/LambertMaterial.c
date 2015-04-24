#include "LambertMaterial.h"

#include <stdlib.h>
#include <math.h>

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

	(void)lambert;
	(void)ray;
	(void)hit;
	(void)newRay;
	(void)intensity;
	return 0;
}

static void		LambertMaterial_deleteMaterial(void *this)
{
	LambertMaterial_delete(this);
}