#include "Material.h"

#include <stdlib.h>

Material	*Material_new()
{
	return Material_init(malloc(sizeof(Material)));
}

void		Material_delete(Material *this)
{
	if (this->data != NULL && this->deletePtr != NULL) {
		this->deletePtr(this->data);
	}
	free(this);
}

Material	*Material_init(Material *this)
{
	this->data = NULL;
	this->computePtr = NULL;
	this->samplePtr = NULL;
	this->deletePtr = NULL;
	return this;
}

void	Material_computeReflectance(Material *this, Color *col, Vec3 *in, Ray *ray, Intersection *hit)
{
	if (this->computePtr != NULL) {
		this->computePtr(this, col, in, ray, hit);
	}
}

int		Material_sampleRay(Material *this, Ray *ray, Intersection *hit, Ray *newRay, Color *intensity)
{
	if (this->samplePtr != NULL) {
		return this->samplePtr(this, ray, hit, newRay, intensity);
	}
	return 0;
}