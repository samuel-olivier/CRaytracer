#ifndef __CAMERA__
#define __CAMERA__

#include "Ray.h"
#include "Vec3.h"
#include "Mat4x4.h"

typedef struct
{
    float       verticalFOV;
    float       horizontalFOV;
    float       aspectRatio;
    Vec3        screenTopLeft;
    float       screenWidth;
    float       screenHeight;
    Mat4x4      matrix;
    float       aperture;
    float       focalPlane;
}               Camera;

Camera  *Camera_new();
void    Camera_delete(Camera *this);
Camera  *Camera_init(Camera *this);

void    Camera_ray(Camera *this, float x, float y, Ray *ray);
void    Camera_lookAt(Camera *this, Vec3 *position, Vec3 *target, Vec3 *up);

void    Camera_setValues(Camera *this, float verticalFOV, float aspectRatio);

#endif