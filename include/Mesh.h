#ifndef __MESH__
#define __MESH__

#include "Object.h"
#include "Vertex.h"
#include "Vec3.h"

typedef struct
{
	Object		**triangles;
	Vertex		**vertexes;
}				Mesh;

Object	*Mesh_new();
void	Mesh_delete(Mesh *this);

int		Mesh_intersect(Object *this, Ray *ray, Intersection *hit);

void	Mesh_makeRectangle(Object *this, float x, float y);
void	Mesh_makeBox(Object *this, float x, float y, float z);

#endif