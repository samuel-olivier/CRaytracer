#ifndef __COLOR__
#define __COLOR__

typedef union
{
	struct
	{
		float r;
		float g;
		float b;
	};
	float 	rgb[3];
}			Color;

void	Color_setValues(Color *this, float r, float g, float b);
void	Color_setValuesInt(Color *this, int r, int g, int b);

#endif