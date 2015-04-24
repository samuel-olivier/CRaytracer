#ifndef __RAYTRACING__
#define __RAYTRACING__

#include "Scene.h"
#include "Ray.h"
#include "Intersection.h"

void	Raytracing_compute(Scene *scene, Ray *ray, Intersection *hit);

#endif