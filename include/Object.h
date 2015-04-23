#ifndef __OBJECT__
#define __OBJECT__

#include "Ray.h"
#include "Intersection.h"

struct sObject;

typedef int		(*IntersectFunc)(struct sObject *this, Ray *ray, Intersection *hit);
typedef void	(*DeleteFunc)(void *this);

typedef struct		sObject
{
	Material		*material;
	void			*data;

	IntersectFunc	intersectPtr;
	DeleteFunc		deletePtr;
}					Object;

Object	*Object_new();
void	Object_delete(Object *this);

int		Object_intersect(Object *this, Ray *ray, Intersection *hit);

#endif