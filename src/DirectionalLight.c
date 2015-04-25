#include "DirectionalLight.h"

#include <stdlib.h>

static void		DirectionalLight_deleteLight(void *this);

Light	*DirectionalLight_new(Vec3 *direction, Color *color, float intensity)
{
	DirectionalLight	*data = malloc(sizeof(*data));
	data->direction = *direction;
	data->color = *color;
	data->intensity = intensity;
    Vec3_normalize(&data->direction);

	Light	*this = Light_new();
	this->data = data;
	this->illuminatePtr = &DirectionalLight_illuminate;
	this->deletePtr = &DirectionalLight_deleteLight;
	return this;
}

void	DirectionalLight_delete(DirectionalLight *this)
{
	free(this);
}

float	DirectionalLight_illuminate(Light *this, Vec3 *pos, Color *col, Vec3 *toLight, Vec3 *ltPos)
{
	DirectionalLight	*directionalLight = this->data;

	Vec3_scaleVector(toLight, &directionalLight->direction, -1.f);
    Vec3_addScaledVectors(ltPos, pos, toLight, 10e6);
    *col = directionalLight->color;
    return directionalLight->intensity;
}

static void	DirectionalLight_deleteLight(void *this)
{
	DirectionalLight_delete(this);
}