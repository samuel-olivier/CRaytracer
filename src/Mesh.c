#include "Mesh.h"

#include <stdlib.h>

#include "Triangle.h"
#include "Config.h"

static void Mesh_deleteObject(void *this);
static void	addFace(Mesh *this, int vIdx, int tIdx, float v0[3], float v1[3], float v2[3], float v3[3], float n[3]);

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
		if (this->material) {
			hit->material = this->material;
		}
		hit->object = this;
	}
	return success;
}

void	Mesh_makeRectangle(Object *this, float x, float y)
{
	Mesh	*mesh = this->data;
	Vec3	normal;
	Vec3 vertex;
	Vec3_setValues(&normal, 0.f, 0.f, 1.f);

	x *= 0.5f;
	y *= 0.5f;
	mesh->vertexes = malloc(sizeof(*mesh->vertexes) * 5);
	Vec3_setValues(&vertex, -x, -y, 0.f);
	mesh->vertexes[0] = Vertex_new(&vertex, &normal);
	Vec3_setValues(&vertex, -x, y, 0.f);
	mesh->vertexes[1] = Vertex_new(&vertex, &normal);
	Vec3_setValues(&vertex, x, y, 0.f);
	mesh->vertexes[2] = Vertex_new(&vertex, &normal);
	Vec3_setValues(&vertex, x, -y, 0.f);
	mesh->vertexes[3] = Vertex_new(&vertex, &normal);
	mesh->vertexes[4] = NULL;
	mesh->triangles = malloc(sizeof(*mesh->triangles) * 3);
	mesh->triangles[0] = Triangle_new(mesh->vertexes[0], mesh->vertexes[1], mesh->vertexes[2]);
	mesh->triangles[1] = Triangle_new(mesh->vertexes[0], mesh->vertexes[2], mesh->vertexes[3]);
	mesh->triangles[2] = NULL;
}


void	Mesh_makeBox(Object *this, float x, float y, float z)
{
	Mesh	*mesh = this->data;

	x *= 0.5f;
	y *= 0.5f;
	z *= 0.5f;
	mesh->vertexes = malloc(sizeof(*mesh->vertexes) * 25);
	mesh->vertexes[24] = NULL;
	mesh->triangles = malloc(sizeof(*mesh->triangles) * 13);
	mesh->triangles[12] = NULL;
	float	p000[3] = {-x, -y, -z};
	float	p001[3] = {-x, -y, z};
	float	p010[3] = {-x, y, -z};
	float	p011[3] = {-x, y, z};
	float	p100[3] = {x, -y, -z};
	float	p101[3] = {x, -y, z};
	float	p110[3] = {x, y, -z};
	float	p111[3] = {x, y, z};

	addFace(mesh, 0, 0, p101, p100, p110, p111, (float[3]){1.f, 0.f, 0.f}); // Right
	addFace(mesh, 4, 2, p001, p000, p010, p011, (float[3]){-1.f, 0.f, 0.f}); // Left
	addFace(mesh, 8, 4, p011, p111, p110, p010, (float[3]){0.f, 1.f, 0.f}); // Top
	addFace(mesh, 12, 6, p001, p101, p100, p000, (float[3]){0.f, -1.f, 0.f}); // Bottom
	addFace(mesh, 16, 8, p001, p101, p111, p011, (float[3]){0.f, 0.f, 1.f}); // Front
	addFace(mesh, 20, 10, p000, p100, p110, p010, (float[3]){0.f, 0.f, -1.f}); // Back
}

static void Mesh_deleteObject(void *this)
{
	Mesh_delete(this);
}

static void	addFace(Mesh *this, int vIdx, int tIdx, float v0[3], float v1[3], float v2[3], float v3[3], float n[3])
{
	Vec3 normal;
	Vec3_setValues(&normal, n[0], n[1], n[2]);
	Vec3 vPos;
	Vec3_setValues(&vPos, v0[0], v0[1], v0[2]);
	this->vertexes[vIdx + 0] = Vertex_new(&vPos, &normal);
	Vec3_setValues(&vPos, v1[0], v1[1], v1[2]);
	this->vertexes[vIdx + 1] = Vertex_new(&vPos, &normal);
	Vec3_setValues(&vPos, v2[0], v2[1], v2[2]);
	this->vertexes[vIdx + 2] = Vertex_new(&vPos, &normal);
	Vec3_setValues(&vPos, v3[0], v3[1], v3[2]);
	this->vertexes[vIdx + 3] = Vertex_new(&vPos, &normal);
	this->triangles[tIdx + 0] = Triangle_new(this->vertexes[vIdx + 0], this->vertexes[vIdx + 1], this->vertexes[vIdx + 2]);
	this->triangles[tIdx + 1] = Triangle_new(this->vertexes[vIdx + 0], this->vertexes[vIdx + 2], this->vertexes[vIdx + 3]);
}
