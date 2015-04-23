#ifndef __VEC3__
#define __VEC3__

typedef union
{
	struct
	{
		float x;
		float y;
		float z;
	};
	float 	xyz[3];
}			Vec3;

Vec3	*Vec3_new();
Vec3	*Vec3_create(float x, float y, float z);
void	Vec3_delete(Vec3 *this);
Vec3	*Vec3_init(Vec3 *this);
Vec3	*Vec3_clone(Vec3 *this);
Vec3	*Vec3_copy(Vec3 *this, Vec3 *from);

Vec3	*Vec3_setValues(Vec3 *this, float x, float y, float z);

Vec3	*Vec3_add(Vec3 *this, Vec3 *other);
Vec3	*Vec3_sub(Vec3 *this, Vec3 *other);
Vec3	*Vec3_mul(Vec3 *this, Vec3 *other);
Vec3	*Vec3_div(Vec3 *this, Vec3 *other);
Vec3	*Vec3_scale(Vec3 *this, float factor);

Vec3	*Vec3_addVectors(Vec3 *this, Vec3 *a, Vec3 *b);
Vec3	*Vec3_subVectors(Vec3 *this, Vec3 *a, Vec3 *b);
Vec3	*Vec3_mulVectors(Vec3 *this, Vec3 *a, Vec3 *b);
Vec3	*Vec3_divVectors(Vec3 *this, Vec3 *a, Vec3 *b);
Vec3	*Vec3_scaleVector(Vec3 *this, Vec3 *other, float factor);

float	Vec3_dot(Vec3 *this, Vec3 *other);
Vec3	*Vec3_cross(Vec3 *this, Vec3 *other);
Vec3	*Vec3_crossVectors(Vec3 *this, Vec3 *a, Vec3 *b);

Vec3	*Vec3_negate(Vec3 *this);
Vec3	*Vec3_normalize(Vec3 *this);
float	Vec3_length(Vec3 *this);
float	Vec3_lengthSquared(Vec3 *this);
float	Vec3_distanceTo(Vec3 *this, Vec3 *point);

#endif
