#include "Material.h"

#include <stdlib.h>
#include <math.h>

#include "Utils.h"
#include "Config.h"

Material	*Material_new()
{
	return Material_init(malloc(sizeof(Material)));
}

void		Material_delete(Material *this)
{
	if (this->data != NULL && this->deletePtr != NULL) {
		this->deletePtr(this->data);
	}
	free(this);
}

Material	*Material_init(Material *this)
{
	this->data = NULL;
	this->computePtr = NULL;
	this->samplePtr = NULL;
	this->deletePtr = NULL;
	return this;
}

void	Material_computeReflectance(Material *this, Color *col, Vec3 *in, Ray *ray, Intersection *hit)
{
	this->computePtr(this, col, in, ray, hit);
}

int		Material_sampleRay(Material *this, Ray *ray, Intersection *hit, Ray *newRay, Color *intensity)
{
	return this->samplePtr(this, ray, hit, newRay, intensity);
}


void	Material_fresnelMetal(Vec3 *d, Vec3 *n, float nt, float kt, float *intensity, Vec3 *rayDirection)
{
	float ndd = Vec3_dot(n, d);
	if (ndd > 0) {
		*intensity = 1.f;
		*rayDirection = *d;
		return ;
	}
	float nd2 = ndd * ndd;
	float nk2 = nt * nt + kt * kt;
	float nnd2 = 2.0f * nt * ndd;

	float rPar = (nk2 * nd2 + nnd2 + 1.0f) / (nk2 * nd2 - nnd2 + 1.0f);
	float rPerp = (nk2 + nd2 + nnd2) / (nk2 + nd2 - nnd2);

	*intensity = 0.5f * (rPar + rPerp);
	*rayDirection = *d;
	Vec3_addScaled(rayDirection, n, -2.f * ndd);
	Vec3_normalize(rayDirection);
}

int		Material_fresnelDielectric(Vec3 *d, Vec3 *normal, float ni, float nt, Vec3 rays[2], float intensities[2])
{
	Vec3	n = *normal;
	float ndd = Vec3_dot(&n, d);
	if (ndd > -EPSILON && ndd < EPSILON) {
		return 0;
	}
	if (ndd > 0) {
		Vec3_negate(&n);
		ndd *= -1;
	}
	Vec3	r = *d;
	Vec3_addScaled(&r, &n, -2.f * ndd);
	Vec3_normalize(&r);

	Vec3	z = *d;
	Vec3_addScaled(&z, &n, -ndd);
	Vec3_scale(&z, ni / nt);
	float z2 = Vec3_lengthSquared(&z);

	if (z2 >= 1.0f) {
		rays[0] = r;
		intensities[0] = 1.f;
		return 1;
	}

	Vec3 t = z;
	Vec3_addScaled(&t, &n, -sqrtf(1.f - z2));
	Vec3_normalize(&t);

	float ndt = Vec3_dot(&n, &t);
	float rPar = (nt * ndd - ni * ndt) / (nt * ndd + ni * ndt);
	float rPerp = (ni * ndd - nt * ndt) / (ni * ndd + nt * ndt);
	float fr = 0.5f * (rPar * rPar + rPerp * rPerp);

	rays[0] = r;
	intensities[0] = fr;
	rays[1] = t;
	intensities[1] = 1.f - fr;
	return 2;
}

float	Material_cookTorrance(Vec3 *v, Vec3 *n, Vec3 *L, float F, float m)
{
	Vec3 h;
	Vec3_addVectors(&h, v, L);
	Vec3_normalize(&h);
	float nh = Vec3_dot(n, &h);
	float nv = Vec3_dot(n, v);
	float vh = Vec3_dot(v, &h);
	float nL = Vec3_dot(n, L);
	float m2 = m * m;
	float alpha = min(0.999, acos(nh));
	float G = min(1.0f, min(2.0f * nh * nv / vh, 2.0f * nh * nL / vh));
	float D = exp(-pow(tan(alpha), 2.0f) / m2) / (m2 * pow(cos(alpha), 4.0f));
	return min(24.0f, F * G * D / (4.0f * M_PI * nL * nv));
}
