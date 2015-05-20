#include "DielectricMaterial.h"

#include <stdlib.h>
#include <math.h>

#include "Utils.h"
#include "Config.h"

static void		DielectricMaterial_deleteMaterial(void *this);

Material	*DielectricMaterial_new()
{
	DielectricMaterial	*data = malloc(sizeof(*data));
	data->n = REFRACTION_INDEX;
	Color_setValues(&data->absorptionColor, 1.f, 1.f, 1.f, 1.f);
	data->absorptionCoef = 0.0f;
	data->roughness = 0.2f;

	Material	*this = Material_new();
	this->data = data;
	this->computePtr = &DielectricMaterial_computeReflectance;
	this->samplePtr = &DielectricMaterial_sampleRay;
	this->deletePtr = &DielectricMaterial_deleteMaterial;
	return this;
}

void		DielectricMaterial_delete(DielectricMaterial *this)
{
	free(this);
}

void	DielectricMaterial_computeReflectance(Material *this, Color *col, Vec3 *in, Ray *ray, Intersection *hit)
{
	DielectricMaterial	*dielectric = this->data;
	float ni = REFRACTION_INDEX;
	float nt = dielectric->n;

	if (ray->refraction != REFRACTION_INDEX) {
		swap(&ni, &nt);
	}

	Vec3	rays[2];
	float	intensities[2];
	int nbRay = Material_fresnelDielectric(&ray->direction, &hit->normal, ni, nt, rays, intensities);
	if (dielectric->roughness > 0.0f && nbRay > 0) {
        Vec3	newDirection = ray->direction;
        Vec3_negate(&newDirection);
		Color_setValues(col, 1.f, 1.f, 1.f, 1.f);
		Color_scale(col, Material_cookTorrance(&newDirection, &hit->normal, in, intensities[0], dielectric->roughness));
	} else {
		Color_setValues(col, 0.f, 0.f, 0.f, 1.f);
	}
}

int		DielectricMaterial_sampleRay(Material *this, Ray *ray, Intersection *hit, Ray *newRay, Color *intensity)
{
	DielectricMaterial	*dielectric = this->data;
	float ni = REFRACTION_INDEX;
	float nt = dielectric->n;
	float absorption = 0.0f;
	Vec3  n = hit->normal;

	if (Vec3_dot(&ray->direction, &n) > 0) {
		Vec3_negate(&n);
		swap(&ni, &nt);
		absorption = dielectric->absorptionCoef;
	}
	Vec3	rays[2];
	float	intensities[2];
	int nbRay = Material_fresnelDielectric(&ray->direction, &n, ni, nt, rays, intensities);
	float s = (float)rand() / RAND_MAX;

	if (nbRay == 1 || (nbRay == 2 && s < intensities[0])) {
		Color_setValues(intensity, 1.f, 1.f, 1.f, 1.f);
		newRay->origin = hit->position;
		newRay->direction = rays[0];
		newRay->refraction = ni;
		newRay->type = ReflectedRay;
	} else if (nbRay == 2) {
		Color_setValues(intensity, 1.f, 1.f, 1.f, 1.f);
		newRay->origin = hit->position;
		newRay->direction = rays[1];
		newRay->refraction = nt;
		newRay->type = TransmittedRay;
		if (absorption > 0.0f) {
			float s = -absorption * Vec3_distanceTo(&hit->position, &ray->origin);
			intensity->r *= exp(s * (1.f - dielectric->absorptionColor.r));
			intensity->g *= exp(s * (1.f - dielectric->absorptionColor.g));
			intensity->b *= exp(s * (1.f - dielectric->absorptionColor.b));
		}
	} else {
		Color_setValues(intensity, 0.f, 0.f, 0.f, 1.f);
		newRay->type = DiffusedRay;
		return 0;
	}
	return 1;
}

static void		DielectricMaterial_deleteMaterial(void *this)
{
	DielectricMaterial_delete(this);
}
