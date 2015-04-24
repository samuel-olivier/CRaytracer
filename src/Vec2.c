#include "Vec2.h"

#include <stdlib.h>
#include <math.h>
#include <stdio.h>

Vec2	*Vec2_new()
{
	return Vec2_init(malloc(sizeof(Vec2)));
}

Vec2	*Vec2_create(float x, float y)
{
	return Vec2_setValues(Vec2_new(), x, y);
}

void	Vec2_delete(Vec2 *this)
{
	free(this);
}

Vec2	*Vec2_init(Vec2 *this)
{
	return Vec2_setValues(this, 0.f, 0.f);
}

Vec2	*Vec2_clone(Vec2 *this)
{
	return Vec2_create(this->x, this->y);
}

Vec2	*Vec2_copy(Vec2 *this, Vec2 *from)
{
	return Vec2_setValues(this, from->x, from->y);
}

Vec2	*Vec2_setValues(Vec2 *this, float x, float y)
{
	this->x = x;
	this->y = y;
	return this;
}

Vec2	*Vec2_add(Vec2 *this, Vec2 *other)
{
	return Vec2_addVectors(this, this, other);
}

Vec2	*Vec2_sub(Vec2 *this, Vec2 *other)
{
	return Vec2_subVectors(this, this, other);
}

Vec2	*Vec2_mul(Vec2 *this, Vec2 *other)
{
	return Vec2_mulVectors(this, this, other);
}

Vec2	*Vec2_div(Vec2 *this, Vec2 *other)
{
	return Vec2_divVectors(this, this, other);
}

Vec2	*Vec2_scale(Vec2 *this, float factor)
{
	return Vec2_scaleVector(this, this, factor);
}

Vec2	*Vec2_addVectors(Vec2 *this, Vec2 *a, Vec2 *b)
{
	return Vec2_setValues(this, a->x + b->x, a->y + b->y);
}

Vec2	*Vec2_subVectors(Vec2 *this, Vec2 *a, Vec2 *b)
{
	return Vec2_setValues(this, a->x - b->x, a->y - b->y);
}

Vec2	*Vec2_mulVectors(Vec2 *this, Vec2 *a, Vec2 *b)
{
	return Vec2_setValues(this, a->x * b->x, a->y * b->y);
}

Vec2	*Vec2_divVectors(Vec2 *this, Vec2 *a, Vec2 *b)
{
	return Vec2_setValues(this, a->x / b->x, a->y / b->y);
}

Vec2	*Vec2_scaleVector(Vec2 *this, Vec2 *other, float factor)
{
	return Vec2_setValues(this, other->x * factor, other->y * factor);
}

float	Vec2_dot(Vec2 *this, Vec2 *other)
{
	return this->x * other->x + this->y * other->y;
}

Vec2	*Vec2_negate(Vec2 *this)
{
	return Vec2_scale(this, -1.f);
}

Vec2	*Vec2_normalize(Vec2 *this)
{
	return Vec2_scale(this, 1.f / Vec2_length(this));
}

float	Vec2_length(Vec2 *this)
{
	return sqrt(Vec2_dot(this, this));
}

float	Vec2_lengthSquared(Vec2 *this)
{
	return Vec2_dot(this, this);
}

float	Vec2_distanceTo(Vec2 *this, Vec2 *point)
{
	Vec2	vec;

	return Vec2_length(Vec2_subVectors(&vec, this, point));
}

void	Vec2_dump(Vec2 *this, char *prefix)
{
	printf("[DEBUG][Vec2] %s : (%f %f)\n", prefix, this->x, this->y);
}