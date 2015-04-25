#ifndef __SCENE__
#define __SCENE__

#include "List.h"
#include "Camera.h"
#include "Ray.h"
#include "Intersection.h"
#include "Object.h"
#include "Light.h"
#include "Color.h"

typedef struct
{
	Camera		*camera;
	List		objects;
	List		lights;
	Color		sky;
}				Scene;

Scene	*Scene_new();
void	Scene_delete(Scene *this);
Scene	*Scene_init(Scene *this);

int		Scene_intersect(Scene *this, Ray *ray, Intersection *hit);

void	Scene_addObject(Scene *this, Object *obj);
void	Scene_addLight(Scene *this, Light *lgt);

#endif