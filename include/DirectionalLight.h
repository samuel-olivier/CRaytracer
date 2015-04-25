#ifndef __DIRECTIONAL_LIGHT__
#define __DIRECTIONAL_LIGHT__

#include "Light.h"
#include "Vec3.h"
#include "Color.h"

typedef struct
{
	Vec3		direction;
	Color		color;
	float		intensity;
}				DirectionalLight;

Light	*DirectionalLight_new(Vec3 *direction, Color *color, float intensity);
void	DirectionalLight_delete(DirectionalLight *this);

float	DirectionalLight_illuminate(Light *this, Vec3 *pos, Color *col, Vec3 *toLight, Vec3 *ltPos);

#endif