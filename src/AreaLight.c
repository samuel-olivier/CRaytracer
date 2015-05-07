#include "AreaLight.h"

#include <stdlib.h>

#include "Utils.h"
#include "Config.h"

static void		AreaLight_deleteLight(void *this);

Light	*AreaLight_new(Color *color, float intensity)
{
	AreaLight	*data = malloc(sizeof(*data));
	Vec3_init(&data->position);
	Vec3_init(&data->u);
	Vec3_init(&data->v);
	Vec3_init(&data->normal);
	data->color = *color;
	data->intensity = intensity;
	data->area = 0;

	Light	*this = Light_new();
	this->data = data;
	this->sampleNumber = LIGHT_SAMPLE_NUMBER;
	this->illuminatePtr = &AreaLight_illuminate;
	this->intersectionPtr = &AreaLight_intersectionColor;
	this->deletePtr = &AreaLight_deleteLight;
	return this;
}

void	AreaLight_delete(AreaLight *this)
{
	free(this);
}

void	AreaLight_makeRectangle(Light *this, Vec3 *position, Vec3 *u, Vec3 *v)
{
	AreaLight	*areaLight = this->data;

	areaLight->position = *position;
	areaLight->u = *u;
	areaLight->v = *v;
	Vec3_crossVectors(&areaLight->normal, u, v);
	Vec3_normalize(&areaLight->normal);
	areaLight->area = Vec3_length(u) * Vec3_length(u);
}

float	AreaLight_illuminate(Light *this, Vec3 *pos, Color *col, Vec3 *toLight, Vec3 *ltPos)
{
	AreaLight	*areaLight = this->data;
	Vec3		u;
	Vec3		v;

	Vec3_scaleVector(&u, &areaLight->u, ((float)rand()) / RAND_MAX);
	Vec3_scaleVector(&v, &areaLight->v, ((float)rand()) / RAND_MAX);
	Vec3_addVectors(ltPos, &u, &v);
	Vec3_add(ltPos, &areaLight->position);
	Vec3_subVectors(toLight, ltPos, pos);
	Vec3_normalize(toLight);
	float bright = M_PI * areaLight->intensity * areaLight->area;
	*col = areaLight->color;
	float cosA = -Vec3_dot(toLight, &areaLight->normal);
	return bright * maxf(cosA, 0.f);
}

void	AreaLight_intersectionColor(Light *this, Color *color)
{
	AreaLight	*areaLight = this->data;

	*color = areaLight->color;
	Color_scale(color, areaLight->intensity / M_PI);
}

static void	AreaLight_deleteLight(void *this)
{
	AreaLight_delete(this);
}
