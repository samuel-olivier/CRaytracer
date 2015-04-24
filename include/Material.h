#ifndef __MATERIAL__
#define __MATERIAL__

#include "Color.h"
#include "Vec3.h"
#include "Intersection.h"
#include "Ray.h"

typedef void	(*Material_ComputeReflectanceFunc)(struct sMaterial *this, Color *col, Vec3 *in, Ray *ray, Intersection *hit);
typedef int		(*Material_SampleRayFunc)(struct sMaterial *this, Ray *ray, Intersection *hit, Ray *newRay, Color *intensity);
typedef void	(*Material_DeleteFunc)(void *this);


typedef struct						sMaterial
{
	void							*data;

	Material_ComputeReflectanceFunc	computePtr;
	Material_SampleRayFunc			samplePtr;
	Material_DeleteFunc				deletePtr;
}									Material;

Material	*Material_new();
void		Material_delete(Material *this);
Material	*Material_init(Material *this);

void	Material_computeReflectance(Material *this, Color *col, Vec3 *in, Ray *ray, Intersection *hit);
int		Material_sampleRay(Material *this, Ray *ray, Intersection *hit, Ray *newRay, Color *intensity);

#endif