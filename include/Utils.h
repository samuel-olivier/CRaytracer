#ifndef __UTILS__
#define __UTILS__

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

float	minf(float a, float b);
int		min(int a, int b);

float	maxf(float a, float b);
int		max(int a, int b);

float	clampf(float value, float min, float max);
int		clamp(int value, int min, int max);

float	degreesToRadians(float deg);
float	radiansToDegrees(float rad);

#endif