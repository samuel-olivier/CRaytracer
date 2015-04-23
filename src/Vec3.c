#include "Vec3.h"

#include <stdlib.h>
#include <math.h>

Vec3	*Vec3_new()
{
	return Vec3_init(malloc(sizeof(Vec3)));
}

Vec3	*Vec3_create(float x, float y, float z)
{
	return Vec3_setValues(Vec3_new(), x, y, z);
}

void	Vec3_delete(Vec3 *this)
{
	free(this);
}

Vec3	*Vec3_init(Vec3 *this)
{
	return Vec3_setValues(this, 0.f, 0.f, 0.f);
}

Vec3	*Vec3_clone(Vec3 *this)
{
	return Vec3_create(this->x, this->y, this->z);
}

Vec3	*Vec3_copy(Vec3 *this, Vec3 *from)
{
	return Vec3_setValues(this, from->x, from->y, from->z);
}

Vec3	*Vec3_setValues(Vec3 *this, float x, float y, float z)
{
	this->x = x;
	this->y = y;
	this->z = z;
	return this;
}

Vec3	*Vec3_add(Vec3 *this, Vec3 *other)
{
	return Vec3_addVectors(this, this, other);
}

Vec3	*Vec3_sub(Vec3 *this, Vec3 *other)
{
	return Vec3_subVectors(this, this, other);
}

Vec3	*Vec3_mul(Vec3 *this, Vec3 *other)
{
	return Vec3_mulVectors(this, this, other);
}

Vec3	*Vec3_div(Vec3 *this, Vec3 *other)
{
	return Vec3_divVectors(this, this, other);
}

Vec3	*Vec3_scale(Vec3 *this, float factor)
{
	return Vec3_scaleVector(this, this, factor);
}

Vec3	*Vec3_addVectors(Vec3 *this, Vec3 *a, Vec3 *b)
{
	return Vec3_setValues(this, a->x + b->x, a->y + b->y, a->z + b->z);
}

Vec3	*Vec3_subVectors(Vec3 *this, Vec3 *a, Vec3 *b)
{
	return Vec3_setValues(this, a->x - b->x, a->y - b->y, a->z - b->z);
}

Vec3	*Vec3_mulVectors(Vec3 *this, Vec3 *a, Vec3 *b)
{
	return Vec3_setValues(this, a->x * b->x, a->y * b->y, a->z * b->z);
}

Vec3	*Vec3_divVectors(Vec3 *this, Vec3 *a, Vec3 *b)
{
	return Vec3_setValues(this, a->x / b->x, a->y / b->y, a->z / b->z);
}

Vec3	*Vec3_scaleVector(Vec3 *this, Vec3 *other, float factor)
{
	return Vec3_setValues(this, other->x * factor, other->y * factor, other->z * factor);
}

float	Vec3_dot(Vec3 *this, Vec3 *other)
{
	return this->x * other->x + this->y * other->y + this->z * other->z;
}

Vec3	*Vec3_cross(Vec3 *this, Vec3 *other)
{
	return Vec3_crossVectors(this, this, other);
}

Vec3	*Vec3_crossVectors(Vec3 *this, Vec3 *a, Vec3 *b)
{
	return Vec3_setValues(this,
		a->y * b->z - a->z * b->y,
		a->z * b->x - a->x * b->z,
		a->x * b->y - a->y * b->x);
}

Vec3	*Vec3_negate(Vec3 *this)
{
	return Vec3_scale(this, -1.f);
}

Vec3	*Vec3_normalize(Vec3 *this)
{
	return Vec3_scale(this, 1.f / Vec3_length(this));
}

float	Vec3_length(Vec3 *this)
{
	return sqrt(Vec3_dot(this, this));
}

float	Vec3_lengthSquared(Vec3 *this)
{
	return Vec3_dot(this, this);
}

float	Vec3_distanceTo(Vec3 *this, Vec3 *point)
{
	Vec3	vec;

	return Vec3_length(Vec3_subVectors(&vec, this, point));
}
