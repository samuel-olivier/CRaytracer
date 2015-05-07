#include "MetalMaterial.h"

#include <stdlib.h>
#include <math.h>

#include "Utils.h"

static void		MetalMaterial_deleteMaterial(void *this);

Material	*MetalMaterial_new(Color *transmittedColor)
{
	MetalMaterial	*data = malloc(sizeof(*data));
	data->transmittedColor = *transmittedColor;
	data->n = 1.f;
	data->k = 1.f;
	data->roughness = 0.1f;

	Material	*this = Material_new();
	this->data = data;
	this->computePtr = &MetalMaterial_computeReflectance;
	this->samplePtr = &MetalMaterial_sampleRay;
	this->deletePtr = &MetalMaterial_deleteMaterial;
	return this;
}

void		MetalMaterial_delete(MetalMaterial *this)
{
	free(this);
}

void	MetalMaterial_computeReflectance(Material *this, Color *col, Vec3 *in, Ray *ray, Intersection *hit)
{
	MetalMaterial	*metal = this->data;

	if (metal->roughness > 0.0f) {
		float	intensityValue = 0;
		Vec3	newDirection;
		Material_fresnelMetal(&ray->direction, &hit->normal, metal->n, metal->k, &intensityValue, &newDirection);
		newDirection = ray->direction;
		Vec3_negate(&newDirection);
		Color_setValues(col, 1.f, 1.f, 1.f, 1.f);
		Color_scale(col, Material_cookTorrance(&newDirection, &hit->normal, in, intensityValue, metal->roughness));
	} else {
		Color_setValues(col, 0.f, 0.f, 0.f, 1.f);
	}
}

int		MetalMaterial_sampleRay(Material *this, Ray *ray, Intersection *hit, Ray *newRay, Color *intensity)
{
	MetalMaterial	*metal = this->data;
	float	intensityValue = 0;
	Vec3	newDirection;

	Material_fresnelMetal(&ray->direction, &hit->normal, metal->n, metal->k, &intensityValue, &newDirection);
	*intensity = metal->transmittedColor;
	Color_scale(intensity, intensityValue);
	newRay->origin = hit->position;
	newRay->direction = newDirection;
	newRay->type = ReflectedRay;
	return 1;
}

static void		MetalMaterial_deleteMaterial(void *this)
{
	MetalMaterial_delete(this);
}