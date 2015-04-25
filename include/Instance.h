#ifndef __TRIANGLE__
#define __TRIANGLE__

#include "Object.h"
#include "Mat4x4.h"

typedef struct
{
	Mat4x4		m;
	Mat4x4		mInv;
	Object		*object;
}				Instance;

Object	*Instance_new(Object *obj);
void	Instance_delete(Instance *this);

int		Instance_intersect(Object *this, Ray *ray, Intersection *hit);

void	Instance_setMatrix(Object *this, Mat4x4 *m);

#endif