#ifndef __MAT4X4__
#define __MAT4X4__

#include "Vec3.h"

typedef union
{
	struct
	{
		float a[4];
		float b[4];
		float c[4];
		float d[4];
	};
	float 	m[4][4];
}				Mat4x4;

Mat4x4	*Mat4x4_new();
void	Mat4x4_delete(Mat4x4 *this);
Mat4x4	*Mat4x4_init(Mat4x4 *this);

void	Mat4x4_toIdentity(Mat4x4 *this);
int		Mat4x4_invertMatrix(Mat4x4 *this, Mat4x4 *other);

void	Mat4x4_setColumnVec3(Mat4x4 *this, int column, Vec3 *fill);
void	Mat4x4_columnVec3(Mat4x4 *this, int column, Vec3 *fill);

void	Mat4x4_mapVec3(Mat4x4 *this, Vec3 *from, Vec3 *to, float w);

void	Mat4x4_translate(Mat4x4 *this, Vec3 *tr);
void	Mat4x4_rotateX(Mat4x4 *this, float t);
void	Mat4x4_rotateY(Mat4x4 *this, float t);
void	Mat4x4_rotateZ(Mat4x4 *this, float t);

void	Mat4x4_dump(Mat4x4 *this, char *prefix);

#endif