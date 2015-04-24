#ifndef __SCENE__
#define __SCENE__

#include "List.h"

typedef struct
{
	Camera		*camera;
	List		objects;
	List		lights;
}				Scene;

Scene	*Scene_new();
void	Scene_delete(Scene *this);
Scene	*Scene_init(Scene *this);

#endif