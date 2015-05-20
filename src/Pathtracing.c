#include "Pathtracing.h"

#include "Light.h"
#include "Material.h"
#include "Config.h"
#include "Utils.h"

static int isShaded(Scene *scene, Vec3 *hitPosition, Vec3 *toLight, Vec3 *lightPos);

void	Pathtracing_compute(Scene *scene, Ray *ray, Intersection *hit)
{
	if (Scene_intersect(scene, ray, hit)) {
		if (hit->object != NULL && hit->object->light != NULL) {
			Light_intersectionColor(hit->object->light, &hit->shade);
			return ;
		}
		if (hit->material == NULL) {
			return ;
		}
		/* if (Vec3_dot(&hit->normal, &ray->direction) > 0) { */
		/* 	Vec3_negate(&hit->normal); */
		/* } */
		LIST_FOREACH(scene->lights, it) {
			Color 		color;
			Vec3	 	toLight;
			Vec3	 	lightPos;
			float 		bright = Light_illuminate(it->data, &hit->position, &color, &toLight, &lightPos);
			float 		cosTheta = Vec3_dot(&toLight, &hit->normal);

			if (cosTheta >= EPSILON && bright >= EPSILON) {
				if (!SHADOW_ENABLED || !isShaded(scene, &hit->position, &toLight, &lightPos)) {
					Color materialColor;
					Color_init(&materialColor);
					Material_computeReflectance(hit->material, &materialColor, &toLight, ray, hit);
					Color_scale(&materialColor, cosTheta * M_PI);
					Color_mul(&color, &materialColor);
					Color_addScaled(&hit->shade, &color, bright);
				}
			}
		}
		if (ray->depth < MAX_RECURSION_DEPTH) {
			Ray		newRay;
			Color	intensity;

			newRay.refraction = ray->refraction;
			if (Material_sampleRay(hit->material, ray, hit, &newRay, &intensity)) {
				newRay.depth = ray->depth + 1;
				Intersection newHit;
				Intersection_init(&newHit);
				Pathtracing_compute(scene, &newRay, &newHit);
				Color_mul(&newHit.shade, &intensity);
				Color_add(&hit->shade, &newHit.shade);
			}
		}
	} else {
		hit->shade = scene->sky;
	}
}

static int isShaded(Scene *scene, Vec3 *hitPosition, Vec3 *toLight, Vec3 *lightPos)
{
    Intersection hit;
    Ray shadowRay;

    Intersection_init(&hit);
    Ray_init(&shadowRay, hitPosition, toLight, ShadowRay);

    hit.hitDistance = Vec3_distanceTo(hitPosition, lightPos);
    return Scene_intersect(scene, &shadowRay, &hit);
}
