#ifndef __COLOR__
#define __COLOR__

typedef union
{
	struct
	{
		float r;
		float g;
		float b;
		float a;
	};
	float 	rgba[4];
}			Color;

Color	*Color_new();
Color	*Color_create(float r, float g, float b, float a);
Color	*Color_create255(int r, int g, int b, int a);
void	Color_delete(Color *this);
Color	*Color_init(Color *this);

Color	*Color_clone(Color *this);
Color	*Color_copy(Color *this, Color *from);

Color	*Color_setValues(Color *this, float r, float g, float b, float a);
Color	*Color_setValues255(Color *this, int r, int g, int b, int a);

Color	*Color_add(Color *this, Color *other);
Color	*Color_sub(Color *this, Color *other);
Color	*Color_mul(Color *this, Color *other);
Color	*Color_div(Color *this, Color *other);
Color	*Color_scale(Color *this, float factor);

Color	*Color_addColors(Color *this, Color *a, Color *b);
Color	*Color_subColors(Color *this, Color *a, Color *b);
Color	*Color_mulColors(Color *this, Color *a, Color *b);
Color	*Color_divColors(Color *this, Color *a, Color *b);
Color	*Color_scaleColor(Color *this, Color *other, float factor);

Color	*Color_normalize(Color *this);
Color	*Color_trunc(Color *this);

#endif