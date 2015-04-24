#include "Mesh.h"

#include <stdlib.h>

#include "Triangle.h"
#include "Config.h"

static void Mesh_deleteObject(void *this);

Object  *Mesh_new()
{
	Mesh	*data = malloc(sizeof(*data));
	data->triangles = NULL;
	data->vertexes = NULL;

	Object  *this = Object_new();
	this->data = data;
	this->intersectPtr = &Mesh_intersect;
	this->deletePtr = &Mesh_deleteObject;   
	return this;
}

void	Mesh_delete(Mesh *this)
{
	free(this);
}

int	 Mesh_intersect(Object *this, Ray *ray, Intersection *hit)
{
	Mesh	*mesh = this->data;
	int	 success = 0;

	for (int i = 0; mesh->triangles && mesh->triangles[i]; ++i) {
		if (Triangle_intersect(mesh->triangles[i], ray, hit)) {
			if (ray->type == ShadowRay) {
				return 1;
			}
			success = 1;
		}
	}
	if (success) {
		hit->material = this->material;
	}
	return success;
}

static void Mesh_deleteObject(void *this)
{
	Mesh_delete(this);
}

void	Mesh_makeRectangle(Object *this, Vec3 points[4])
{
	Mesh	*mesh = this->data;
	Vec3	a, b, normal;
	Vec3_subVectors(&a, &points[1], &points[0]);
	Vec3_subVectors(&b, &points[2], &points[0]);
	Vec3_crossVectors(&normal, &a, &b);
	mesh->vertexes = malloc(sizeof(*mesh->vertexes) * 5);
	for (int i = 0; i < 4; ++i) {
		mesh->vertexes[i] = Vertex_new(&points[i], &normal);
	}
	mesh->vertexes[4] = NULL;
	mesh->triangles = malloc(sizeof(*mesh->triangles) * 3);
	mesh->triangles[0] = Triangle_new(mesh->vertexes[0], mesh->vertexes[1], mesh->vertexes[2]);
	mesh->triangles[1] = Triangle_new(mesh->vertexes[0], mesh->vertexes[2], mesh->vertexes[3]);
	mesh->triangles[2] = NULL;
}
