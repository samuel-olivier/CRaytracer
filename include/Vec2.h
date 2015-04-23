#ifndef __VEC2__
#define __VEC2__

typedef union
{
	struct
	{
		float x;
		float y;
	};
	float 	xy[2];
}			Vec2;

Vec2	*Vec2_new();
Vec2	*Vec2_create(float x, float y);
void	Vec2_delete(Vec2 *this);
Vec2	*Vec2_init(Vec2 *this);
Vec2	*Vec2_clone(Vec2 *this);
Vec2	*Vec2_copy(Vec2 *this, Vec2 *from);

Vec2	*Vec2_setValues(Vec2 *this, float x, float y);

Vec2	*Vec2_add(Vec2 *this, Vec2 *other);
Vec2	*Vec2_sub(Vec2 *this, Vec2 *other);
Vec2	*Vec2_mul(Vec2 *this, Vec2 *other);
Vec2	*Vec2_div(Vec2 *this, Vec2 *other);
Vec2	*Vec2_scale(Vec2 *this, float factor);

Vec2	*Vec2_addVectors(Vec2 *this, Vec2 *a, Vec2 *b);
Vec2	*Vec2_subVectors(Vec2 *this, Vec2 *a, Vec2 *b);
Vec2	*Vec2_mulVectors(Vec2 *this, Vec2 *a, Vec2 *b);
Vec2	*Vec2_divVectors(Vec2 *this, Vec2 *a, Vec2 *b);
Vec2	*Vec2_scaleVector(Vec2 *this, Vec2 *other, float factor);

float	Vec2_dot(Vec2 *this, Vec2 *other);

Vec2	*Vec2_negate(Vec2 *this);
Vec2	*Vec2_normalize(Vec2 *this);
float	Vec2_length(Vec2 *this);
float	Vec2_lengthSquared(Vec2 *this);
float	Vec2_distanceTo(Vec2 *this, Vec2 *point);

#endif
