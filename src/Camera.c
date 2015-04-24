#include "Camera.h"

#include <stdlib.h>
#include <math.h>

#include "Utils.h"

Camera  *Camera_new()
{
	return Camera_init(malloc(sizeof(Camera)));
}

void    Camera_delete(Camera *this)
{
	free(this);
}

Camera  *Camera_init(Camera *this)
{
	this->verticalFOV = 0.f;
	this->horizontalFOV = 0.f;
	this->aspectRatio = 0.f;
	Vec3_init(&this->screenTopLeft);
	this->screenWidth = 0.f;
	this->screenHeight = 0.f;
	Mat4x4_init(&this->matrix);
	return this;
}

void    Camera_ray(Camera *this, float x, float y, Ray *ray)
{
	Vec3 v0, v1;

	Mat4x4_columnVec3(&this->matrix, 0, &v0);
	Mat4x4_columnVec3(&this->matrix, 1, &v1);
	Mat4x4_columnVec3(&this->matrix, 3, &ray->origin);

	Vec3_copy(&ray->direction, &this->screenTopLeft);
	Vec3_add(&ray->direction, Vec3_scale(&v0, x * this->screenWidth));
	Vec3_add(&ray->direction, Vec3_scale(&v1, y * this->screenHeight));
	Vec3_sub(&ray->direction, &ray->origin);
	Vec3_normalize(&ray->direction);
}

void    Camera_lookAt(Camera *this, Vec3 *position, Vec3 *target, Vec3 *up)
{
    Vec3 d = *position;
    Vec3 c;
    Vec3_subVectors(&c, &d, target);
    Vec3_normalize(&c);
    Vec3 a;
    Vec3_crossVectors(&a, up, &c);
    Vec3_normalize(&a);
    Vec3 b;
    Vec3_crossVectors(&b, &c, &a);
    Mat4x4_setColumnVec3(&this->matrix, 0, &a);
    Mat4x4_setColumnVec3(&this->matrix, 1, &b);
    Mat4x4_setColumnVec3(&this->matrix, 2, &c);
    Mat4x4_setColumnVec3(&this->matrix, 3, &d);
    Camera_setValues(this, radiansToDegrees(this->verticalFOV), this->aspectRatio);
}

void    Camera_setValues(Camera *this, float verticalFOV, float aspectRatio)
{
    this->verticalFOV = degreesToRadians(verticalFOV);
    this->aspectRatio = aspectRatio;
    this->screenHeight = tanf(this->verticalFOV / 2.f);
    this->horizontalFOV = 2.f * atanf(this->aspectRatio * this->screenHeight);
    this->screenHeight *= 2.f;
    this->screenWidth = this->screenHeight * this->aspectRatio;
	Vec3 v0, v1, v2, v3;

	Mat4x4_columnVec3(&this->matrix, 0, &v0);
	Mat4x4_columnVec3(&this->matrix, 1, &v1);
	Mat4x4_columnVec3(&this->matrix, 2, &v2);
	Mat4x4_columnVec3(&this->matrix, 3, &v3);

	Vec3_scaleVector(&this->screenTopLeft, &v2, -1.f);
	Vec3_scale(&v0, -this->screenWidth / 2.f);
	Vec3_scale(&v1, this->screenHeight / 2.f);

	Vec3_add(&this->screenTopLeft, &v0);
	Vec3_add(&this->screenTopLeft, &v1);
	Vec3_add(&this->screenTopLeft, &v3);
}
