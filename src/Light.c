#include "Light.h"

#include <stdlib.h>

Light	*Light_new()
{
	return Light_init(malloc(sizeof(Light)));
}

void	Light_delete(Light *this)
{
	if (this->data != NULL && this->deletePtr != NULL) {
		this->deletePtr(this->data);
	}
	free(this);
}

Light	*Light_init(Light *this)
{
	this->data = NULL;
	this->illuminatePtr = NULL;
	this->intersectionPtr = NULL;
	this->deletePtr = NULL;
	return this;
}

float	Light_illuminate(Light *this, Vec3 *pos, Color *col, Vec3 *toLight, Vec3 *ltPos)
{
	return this->illuminatePtr(this, pos, col, toLight, ltPos);
}

void	Light_intersectionColor(Light *this, Color *color)
{
	this->intersectionPtr(this, color);
}
