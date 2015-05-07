#include "Integrator.h"

#include <stdlib.h>

#include "Raytracing.h"
#include "Pathtracing.h"

typedef struct
{
	IntegratorType	type;
	ComputeFct		compute;
}				IntegratorDescription;

static IntegratorDescription	desc[] =
{
	{Raytracing, &Raytracing_compute},
	{Pathtracing, &Pathtracing_compute}
};

Integrator	*Integrator_new(IntegratorType type)
{
	return Integrator_init(malloc(sizeof(Integrator)), type);
}

void		Integrator_delete(Integrator *this)
{
	free(this);
}

Integrator	*Integrator_init(Integrator *this, IntegratorType type)
{
	for (unsigned int i = 0; i < sizeof(desc) / sizeof(*desc); ++i) {
		if (type == desc[i].type) {
			this->type = type;
			this->computePtr = desc[i].compute;
			return this;
		}
	}
	this->type = IntegratorNone;
	this->computePtr = NULL;
	return this;
}

void		Integrator_compute(Integrator *this, Scene *scene, Ray *ray, Intersection *hit)
{
	this->computePtr(scene, ray, hit);
}
