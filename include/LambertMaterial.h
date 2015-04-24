#ifndef __LAMBERT_MATERIAL__
#define __LAMBERT_MATERIAL__

#include "Material.h"
#include "Color.h"

typedef struct
{
	Color		diffuseColor;
}				LambertMaterial;

Material	*LambertMaterial_new(Color *diffuseColor);
void		LambertMaterial_delete(LambertMaterial *this);

void	LambertMaterial_computeReflectance(Material *this, Color *col, Vec3 *in, Ray *ray, Intersection *hit);
int		LambertMaterial_sampleRay(Material *this, Ray *ray, Intersection *hit, Ray *newRay, Color *intensity);

#endif