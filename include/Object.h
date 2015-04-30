#ifndef __OBJECT__
#define __OBJECT__

#include "Ray.h"
#include "Intersection.h"
#include "Material.h"
#include "Light.h"

struct sObject;

typedef int		(*Object_IntersectFunc)(struct sObject *this, Ray *ray, Intersection *hit);
typedef void	(*Object_DeleteFunc)(void *this);

typedef struct		sObject
{
	Material				*material;
	Light					*light;
	void					*data;

	Object_IntersectFunc	intersectPtr;
	Object_DeleteFunc		deletePtr;
}					Object;

Object	*Object_new();
void	Object_delete(Object *this);

int		Object_intersect(Object *this, Ray *ray, Intersection *hit);

#endif
