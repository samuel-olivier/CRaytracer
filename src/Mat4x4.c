#include "Mat4x4.h"

#include <stdlib.h>
#include <string.h>

Mat4x4	*Mat4x4_new()
{
	return Mat4x4_init(malloc(sizeof(Mat4x4)));
}

void	Mat4x4_delete(Mat4x4 *this)
{
	free(this);
}

Mat4x4	*Mat4x4_init(Mat4x4 *this)
{
	Mat4x4_toIdentity(this);
	return this;
}

void	Mat4x4_toIdentity(Mat4x4 *this)
{
	float m[4][4] = {
		{1.f, 0.f, 0.f, 0.f},
		{0.f, 1.f, 0.f, 0.f},
		{0.f, 0.f, 1.f, 0.f},
		{0.f, 0.f, 0.f, 1.f},
	};
	memcpy(this->m, m, sizeof(m));
}

void	Mat4x4_setColumnVec3(Mat4x4 *this, int column, Vec3 *fill)
{
	this->m[column][0] = fill->xyz[0];
	this->m[column][1] = fill->xyz[1];
	this->m[column][2] = fill->xyz[2];
}

void	Mat4x4_columnVec3(Mat4x4 *this, int column, Vec3 *fill)
{
	Vec3_setValues(fill,
		this->m[column][0],
		this->m[column][1],
		this->m[column][2]);
}