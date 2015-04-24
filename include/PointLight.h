#ifndef __POINT_LIGHT__
#define __POINT_LIGHT__

#include "Light.h"
#include "Vec3.h"
#include "Color.h"

typedef struct
{
	Vec3		position;
	Color		color;
	float		intensity;
}				PointLight;

Light	*PointLight_new(Vec3 *position, Color *color, float intensity);
void	PointLight_delete(PointLight *this);

float	PointLight_illuminate(Light *this, Vec3 *pos, Color *col, Vec3 *toLight, Vec3 *ltPos);

#endif