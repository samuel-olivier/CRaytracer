#ifndef __OBJECT__
#define __OBJECT__

typedef int	(*IntersectFunc)(Ray *ray, Intersection *hit);

typedef struct
{
	IntersectFunc	intersectPtr;
	Material		*material;
	void			*data;
}					Object;

#endif