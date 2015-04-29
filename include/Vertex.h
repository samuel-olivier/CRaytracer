#ifndef __VERTEX__
#define __VERTEX__

#include "Vec3.h"

typedef struct
{
	Vec3		position;
	Vec3		normal;
	Vec3		u;
	Vec3		v;
}				Vertex;

Vertex	*Vertex_new(Vec3 *position, Vec3 *normal);
void	Vertex_delete(Vertex *this);
Vertex	*Vertex_init(Vertex *this, Vec3 *position, Vec3 *normal);

void	Vertex_generateTangents(Vertex *this);

#endif