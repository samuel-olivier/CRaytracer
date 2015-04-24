#include "Vertex.h"

#include <stdlib.h>

Vertex	*Vertex_new(Vec3 *position, Vec3 *normal)
{
	return Vertex_init(malloc(sizeof(Vertex)), position, normal);
}

void	Vertex_delete(Vertex *this)
{
	free(this);
}

Vertex	*Vertex_init(Vertex *this, Vec3 *position, Vec3 *normal)
{
	this->position = *position;
	this->normal = *normal;
	return this;
}
