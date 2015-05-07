#ifndef __METAL_MATERIAL__
#define __METAL_MATERIAL__

#include "Material.h"
#include "Color.h"

typedef struct
{
	Color		transmittedColor;
	float		n;
	float		k;
	float		roughness;
}				MetalMaterial;

Material	*MetalMaterial_new(Color *transmittedColor);
void		MetalMaterial_delete(MetalMaterial *this);

void	MetalMaterial_computeReflectance(Material *this, Color *col, Vec3 *in, Ray *ray, Intersection *hit);
int		MetalMaterial_sampleRay(Material *this, Ray *ray, Intersection *hit, Ray *newRay, Color *intensity);

#endif