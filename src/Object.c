#include "Object.h"

#include <stdlib.h>

Object	*Object_new()
{
	Object	*this = malloc(sizeof(*this));

	this->material = NULL;
	this->data = NULL;
	this->intersectPtr = NULL;
	this->deletePtr = NULL;
	return this;
}

void	Object_delete(Object *this)
{
	if (this->data != NULL && this->deletePtr != NULL) {
		this->deletePtr(this->data);
	}
	free(this);
}

int		Object_intersect(Object *this, Ray *ray, Intersection *hit)
{
	if (this->intersectPtr != NULL) {
		return this->intersectPtr(this, ray, hit);
	}
	return 0;
}
