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
void	Mat4x4_setColumnVec3(Mat4x4 *this, int column, Vec3 *fill);
void	Mat4x4_columnVec3(Mat4x4 *this, int column, Vec3 *fill);

#endif