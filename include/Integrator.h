#ifndef __INTEGRATOR__
#define __INTEGRATOR__

#include "Ray.h"
#include "Intersection.h"
#include "Scene.h"

typedef enum 	{Raytracing, Pathtracing, IntegratorNone} IntegratorType;

typedef void	(*ComputeFct)(Scene *scene, Ray *ray, Intersection *hit);

typedef struct
{
	IntegratorType	type;
	ComputeFct		computePtr;
}					Integrator;

Integrator	*Integrator_new(IntegratorType type);
void		Integrator_delete(Integrator *this);
Integrator	*Integrator_init(Integrator *this, IntegratorType type);

void		Integrator_compute(Integrator *this, Scene *scene, Ray *ray, Intersection *hit);

#endif