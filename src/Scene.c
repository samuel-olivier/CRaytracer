#include "Scene.h"

#include <stdlib.h>


Scene	*Scene_new()
{
	return Scene_init(malloc(sizeof(Scene)));
}

void	Scene_delete(Scene *this)
{
	free(this);
}

Scene	*Scene_init(Scene *this)
{
	this->camera = NULL;
	this->objects = List_new();
	this->lights = List_new();
	Color_setValues(&this->sky, 0.f, 0.f, 0.f, 0.f);
	return this;
}

int		Scene_intersect(Scene *this, Ray *ray, Intersection *hit)
{
	int success = 0;
	
	LIST_FOREACH(this->objects, it) {
		if (Object_intersect(it->data, ray, hit)) {
			if (ray->type == ShadowRay) {
				return 1;
			}
			success = 1;
		}
	}
	return success;
}

void	Scene_addObject(Scene *this, Object *obj)
{
	List_append(&this->objects, obj);
}

void	Scene_addLight(Scene *this, Light *lgt)
{
	List_append(&this->lights, lgt);
}