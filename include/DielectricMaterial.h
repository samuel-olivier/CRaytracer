#ifndef __DIELECTRIC_MATERIAL__
#define __DIELECTRIC_MATERIAL__

#include "Material.h"
#include "Color.h"

typedef struct
{
	float		n;
	Color		absorptionColor;
	float		absorptionCoef;
	float		roughness;
}				DielectricMaterial;

Material	*DielectricMaterial_new();
void		DielectricMaterial_delete(DielectricMaterial *this);

void	DielectricMaterial_computeReflectance(Material *this, Color *col, Vec3 *in, Ray *ray, Intersection *hit);
int		DielectricMaterial_sampleRay(Material *this, Ray *ray, Intersection *hit, Ray *newRay, Color *intensity);

#endif