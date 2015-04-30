#ifndef __AREA_LIGHT__
#define __AREA_LIGHT__

#include "Light.h"
#include "Vec3.h"
#include "Color.h"

typedef struct
{
	Vec3		position;
	Vec3		u;
	Vec3		v;
	Vec3		normal;
	Color		color;
	float		intensity;
	float		area;
}				AreaLight;

Light	*AreaLight_new(Color *color, float intensity);
void	AreaLight_delete(AreaLight *this);

void	AreaLight_makeRectangle(Light *this, Vec3 *position, Vec3 *u, Vec3 *v);

float	AreaLight_illuminate(Light *this, Vec3 *pos, Color *col, Vec3 *toLight, Vec3 *ltPos);

#endif
