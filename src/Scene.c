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
	return this;
}
