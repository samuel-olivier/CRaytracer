#include "PointLight.h"

#include <stdlib.h>

static void		PointLight_deleteLight(void *this);

Light	*PointLight_new(Vec3 *position, Color *color, float intensity)
{
	PointLight	*data = malloc(sizeof(*data));
	data->position = *position;
	data->color = *color;
	data->intensity = intensity;

	Light	*this = Light_new();
	this->data = data;
	this->illuminatePtr = &PointLight_illuminate;
	this->deletePtr = &PointLight_deleteLight;
	return this;
}

void	PointLight_delete(PointLight *this)
{
	free(this);
}

float	PointLight_illuminate(Light *this, Vec3 *pos, Color *col, Vec3 *toLight, Vec3 *ltPos)
{
	PointLight	*pointLight = this->data;

    *ltPos = pointLight->position;
    Vec3_subVectors(toLight, ltPos, pos);
    float bright = pointLight->intensity / Vec3_lengthSquared(toLight);
    Vec3_normalize(toLight);
    *col = pointLight->color;
    return bright;
}

static void	PointLight_deleteLight(void *this)
{
	PointLight_delete(this);
}