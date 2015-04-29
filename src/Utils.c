#include "Utils.h"

float	minf(float a, float b)
{
	return a < b ? a : b;
}

int		min(int a, int b)
{
	return a < b ? a : b;
}

float	maxf(float a, float b)
{
	return a > b ? a : b;
}

int		max(int a, int b)
{
	return a > b ? a : b;
}

float	clampf(float value, float lowerBound, float upperBound)
{
	return maxf(lowerBound, minf(upperBound, value));
}

int		clamp(int value, int lowerBound, int upperBound)
{
	return max(lowerBound, min(upperBound, value));
}

float	degreesToRadians(float deg)
{
	return deg * M_PI / 180.f;
}

float	radiansToDegrees(float rad)
{
	return rad * 180.f / M_PI;
}
