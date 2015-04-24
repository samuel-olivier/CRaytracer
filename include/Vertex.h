#ifndef __VERTEX__
#define __VERTEX__

#include "Vec3.h"

typedef struct
{
	Vec3		position;
	Vec3		normal;
}				Vertex;

Vertex	*Vertex_new(Vec3 *position, Vec3 *normal);
void	Vertex_delete(Vertex *this);
Vertex	*Vertex_init(Vertex *this, Vec3 *position, Vec3 *normal);

#endif