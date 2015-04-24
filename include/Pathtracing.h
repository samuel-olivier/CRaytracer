#ifndef __PATHTRACING__
#define __PATHTRACING__

#include "Scene.h"
#include "Ray.h"
#include "Intersection.h"

void	Pathtracing_compute(Scene *scene, Ray *ray, Intersection *hit);

#endif