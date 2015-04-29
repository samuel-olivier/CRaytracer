#include "Mat4x4.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

static float	mulSumRow(Mat4x4 *this, int row, Vec3 *v, float w);

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

int		Mat4x4_invertMatrix(Mat4x4 *this, Mat4x4 *other)
{
	float	inv[4][4];
	float	det;
 
	inv[0][0] =  other->m[1][1] * other->m[2][2] * other->m[3][3] - other->m[1][1] * other->m[2][3] * other->m[3][2] - other->m[2][1] * other->m[1][2] * other->m[3][3] + other->m[2][1] * other->m[1][3] * other->m[3][2] + other->m[3][1] * other->m[1][2] * other->m[2][3] - other->m[3][1] * other->m[1][3] * other->m[2][2];
	inv[1][0] = -other->m[1][0] * other->m[2][2] * other->m[3][3] + other->m[1][0] * other->m[2][3] * other->m[3][2] + other->m[2][0] * other->m[1][2] * other->m[3][3] - other->m[2][0] * other->m[1][3] * other->m[3][2] - other->m[3][0] * other->m[1][2] * other->m[2][3] + other->m[3][0] * other->m[1][3] * other->m[2][2];
	inv[2][0] =  other->m[1][0] * other->m[2][1] * other->m[3][3] - other->m[1][0] * other->m[2][3] * other->m[3][1] - other->m[2][0] * other->m[1][1] * other->m[3][3] + other->m[2][0] * other->m[1][3] * other->m[3][1] + other->m[3][0] * other->m[1][1] * other->m[2][3] - other->m[3][0] * other->m[1][3] * other->m[2][1];
	inv[3][0] = -other->m[1][0] * other->m[2][1] * other->m[3][2] + other->m[1][0] * other->m[2][2] * other->m[3][1] + other->m[2][0] * other->m[1][1] * other->m[3][2] - other->m[2][0] * other->m[1][2] * other->m[3][1] - other->m[3][0] * other->m[1][1] * other->m[2][2] + other->m[3][0] * other->m[1][2] * other->m[2][1];
	inv[0][1] = -other->m[0][1] * other->m[2][2] * other->m[3][3] + other->m[0][1] * other->m[2][3] * other->m[3][2] + other->m[2][1] * other->m[0][2] * other->m[3][3] - other->m[2][1] * other->m[0][3] * other->m[3][2] - other->m[3][1] * other->m[0][2] * other->m[2][3] + other->m[3][1] * other->m[0][3] * other->m[2][2];
	inv[1][1] =  other->m[0][0] * other->m[2][2] * other->m[3][3] - other->m[0][0] * other->m[2][3] * other->m[3][2] - other->m[2][0] * other->m[0][2] * other->m[3][3] + other->m[2][0] * other->m[0][3] * other->m[3][2] + other->m[3][0] * other->m[0][2] * other->m[2][3] - other->m[3][0] * other->m[0][3] * other->m[2][2];
	inv[2][1] = -other->m[0][0] * other->m[2][1] * other->m[3][3] + other->m[0][0] * other->m[2][3] * other->m[3][1] + other->m[2][0] * other->m[0][1] * other->m[3][3] - other->m[2][0] * other->m[0][3] * other->m[3][1] - other->m[3][0] * other->m[0][1] * other->m[2][3] + other->m[3][0] * other->m[0][3] * other->m[2][1];
	inv[3][1] =  other->m[0][0] * other->m[2][1] * other->m[3][2] - other->m[0][0] * other->m[2][2] * other->m[3][1] - other->m[2][0] * other->m[0][1] * other->m[3][2] + other->m[2][0] * other->m[0][2] * other->m[3][1] + other->m[3][0] * other->m[0][1] * other->m[2][2] - other->m[3][0] * other->m[0][2] * other->m[2][1];
	inv[0][2] =  other->m[0][1] * other->m[1][2] * other->m[3][3] - other->m[0][1] * other->m[1][3] * other->m[3][2] - other->m[1][1] * other->m[0][2] * other->m[3][3] + other->m[1][1] * other->m[0][3] * other->m[3][2] + other->m[3][1] * other->m[0][2] * other->m[1][3] - other->m[3][1] * other->m[0][3] * other->m[1][2];
	inv[1][2] = -other->m[0][0] * other->m[1][2] * other->m[3][3] + other->m[0][0] * other->m[1][3] * other->m[3][2] + other->m[1][0] * other->m[0][2] * other->m[3][3] - other->m[1][0] * other->m[0][3] * other->m[3][2] - other->m[3][0] * other->m[0][2] * other->m[1][3] + other->m[3][0] * other->m[0][3] * other->m[1][2];
	inv[2][2] =  other->m[0][0] * other->m[1][1] * other->m[3][3] - other->m[0][0] * other->m[1][3] * other->m[3][1] - other->m[1][0] * other->m[0][1] * other->m[3][3] + other->m[1][0] * other->m[0][3] * other->m[3][1] + other->m[3][0] * other->m[0][1] * other->m[1][3] - other->m[3][0] * other->m[0][3] * other->m[1][1];
	inv[3][2] = -other->m[0][0] * other->m[1][1] * other->m[3][2] + other->m[0][0] * other->m[1][2] * other->m[3][1] + other->m[1][0] * other->m[0][1] * other->m[3][2] - other->m[1][0] * other->m[0][2] * other->m[3][1] - other->m[3][0] * other->m[0][1] * other->m[1][2] + other->m[3][0] * other->m[0][2] * other->m[1][1];
	inv[0][3] = -other->m[0][1] * other->m[1][2] * other->m[2][3] + other->m[0][1] * other->m[1][3] * other->m[2][2] + other->m[1][1] * other->m[0][2] * other->m[2][3] - other->m[1][1] * other->m[0][3] * other->m[2][2] - other->m[2][1] * other->m[0][2] * other->m[1][3] + other->m[2][1] * other->m[0][3] * other->m[1][2];
	inv[1][3] =  other->m[0][0] * other->m[1][2] * other->m[2][3] - other->m[0][0] * other->m[1][3] * other->m[2][2] - other->m[1][0] * other->m[0][2] * other->m[2][3] + other->m[1][0] * other->m[0][3] * other->m[2][2] + other->m[2][0] * other->m[0][2] * other->m[1][3] - other->m[2][0] * other->m[0][3] * other->m[1][2];
	inv[2][3] = -other->m[0][0] * other->m[1][1] * other->m[2][3] + other->m[0][0] * other->m[1][3] * other->m[2][1] + other->m[1][0] * other->m[0][1] * other->m[2][3] - other->m[1][0] * other->m[0][3] * other->m[2][1] - other->m[2][0] * other->m[0][1] * other->m[1][3] + other->m[2][0] * other->m[0][3] * other->m[1][1];
	inv[3][3] =  other->m[0][0] * other->m[1][1] * other->m[2][2] - other->m[0][0] * other->m[1][2] * other->m[2][1] - other->m[1][0] * other->m[0][1] * other->m[2][2] + other->m[1][0] * other->m[0][2] * other->m[2][1] + other->m[2][0] * other->m[0][1] * other->m[1][2] - other->m[2][0] * other->m[0][2] * other->m[1][1];

	det = other->m[0][0] * inv[0][0] + other->m[0][1] * inv[1][0] + other->m[0][2] * inv[2][0] + other->m[0][3] * inv[3][0];

	if (det == 0)
		return 0;

	det = 1.f / det;

	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			this->m[i][j] = inv[i][j] * det;
		}
	}
	return 1;
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

void	Mat4x4_mapVec3(Mat4x4 *this, Vec3 *from, Vec3 *to, float w)
{
	Vec3_setValues(to,
		mulSumRow(this, 0, from, w),
		mulSumRow(this, 1, from, w),
		mulSumRow(this, 2, from, w));
}

void	Mat4x4_translate(Mat4x4 *this, Vec3 *tr)
{
	for (int i = 0; i < 3; ++i) {
		this->m[3][i] += tr->xyz[i];
	}
}

void	Mat4x4_rotateX(Mat4x4 *this, float t)
{
	float	cost = cosf(t);
	float	sint = sinf(t);

	this->m[1][1] = cost;
	this->m[1][2] = sint;
	this->m[2][1] = -sint;
	this->m[2][2] = cost;	
}

void	Mat4x4_rotateY(Mat4x4 *this, float t)
{
	float	cost = cosf(t);
	float	sint = sinf(t);

	this->m[0][0] = cost;
	this->m[2][0] = sint;
	this->m[0][2] = -sint;
	this->m[2][2] = cost;	
}

void	Mat4x4_rotateZ(Mat4x4 *this, float t)
{
	float	cost = cosf(t);
	float	sint = sinf(t);

	this->m[0][0] = cost;
	this->m[0][1] = sint;
	this->m[1][0] = -sint;
	this->m[1][1] = cost;	
}

void	Mat4x4_dump(Mat4x4 *this, char *prefix)
{
	printf("[DEBUG] %s : [\n", prefix);
	for (int i = 0; i <4; ++i) {
		printf("\t %f %f %f %f\n", this->m[0][i], this->m[1][i], this->m[2][i], this->m[3][i]);
	}
	printf("\t]\n");
}

static float	mulSumRow(Mat4x4 *this, int row, Vec3 *v, float w)
{
	float		res = 0.f;

	for (int i = 0; i < 4; ++i) {
		res += (i == 3 ? w : v->xyz[i]) * this->m[i][row];
	}
	return res;
}