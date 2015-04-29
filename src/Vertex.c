#include "Vertex.h"

#include <stdlib.h>

#include "Config.h"

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
	Vertex_generateTangents(this);
	return this;
}

void	Vertex_generateTangents(Vertex *this)
{
	Vec3	up;
	Vec3_setValues(&up, 0.f, 1.f, 0.f);
	Vec3_crossVectors(&this->u, &up, &this->normal);
	if (Vec3_lengthSquared(&this->u) < EPSILON) {
		Vec3_setValues(&this->u, 1.f, 0.f, 0.f);
	} else {
		Vec3_normalize(&this->u);
	}
	Vec3_crossVectors(&this->v, &this->normal, &this->u);
}