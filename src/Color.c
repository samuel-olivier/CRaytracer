#include "Color.h"

#include <stdlib.h>
#include <math.h>

#include "Utils.h"

Color	*Color_new()
{
	return Color_init(malloc(sizeof(Color)));
}

Color	*Color_create(float r, float g, float b, float a)
{
	return Color_setValues(Color_new(), r, g, b, a);
}

Color	*Color_create255(int r, int g, int b, int a)
{
	return Color_setValues255(Color_new(), r, g, b, a);
}

void	Color_delete(Color *this)
{
	free(this);
}

Color	*Color_init(Color *this)
{
	return Color_setValues(this, 0.f, 0.f, 0.f, 1.f);
}

Color	*Color_clone(Color *this)
{
	return Color_create(this->r, this->g, this->b, this->a);
}

Color	*Color_copy(Color *this, Color *from)
{
	return Color_setValues(this, from->r, from->g, from->b, from->a);
}

Color	*Color_setValues(Color *this, float r, float g, float b, float a)
{
	this->r = r;
	this->g = g;
	this->b = b;
	this->a = a;
	return this;
}

Color	*Color_setValues255(Color *this, int r, int g, int b, int a)
{
	return Color_setValues(this,
		(float)r / 255.f,
		(float)g / 255.f,
		(float)b / 255.f,
		(float)a / 255.f);
}

Color	*Color_add(Color *this, Color *other)
{
	return Color_addColors(this, this, other);
}

Color	*Color_sub(Color *this, Color *other)
{
	return Color_subColors(this, this, other);
}

Color	*Color_mul(Color *this, Color *other)
{
	return Color_mulColors(this, this, other);
}

Color	*Color_div(Color *this, Color *other)
{
	return Color_divColors(this, this, other);
}

Color	*Color_scale(Color *this, float factor)
{
	return Color_scaleColor(this, this, factor);
}

Color	*Color_addColors(Color *this, Color *a, Color *b)
{
	return Color_setValues(this,
		a->r + b->r,
		a->g + b->g,
		a->b + b->b,
		a->a + b->a);
}

Color	*Color_subColors(Color *this, Color *a, Color *b)
{
	return Color_setValues(this,
		a->r - b->r,
		a->g - b->g,
		a->b - b->b,
		a->a - b->a);
}

Color	*Color_mulColors(Color *this, Color *a, Color *b)
{
	return Color_setValues(this,
		a->r * b->r,
		a->g * b->g,
		a->b * b->b,
		a->a * b->a);
}

Color	*Color_divColors(Color *this, Color *a, Color *b)
{
	return Color_setValues(this,
		a->r / b->r,
		a->g / b->g,
		a->b / b->b,
		a->a / b->a);
}

Color	*Color_scaleColor(Color *this, Color *other, float factor)
{
	return Color_setValues(this,
		other->r * factor,
		other->g * factor,
		other->b * factor,
		other->a * factor);
}

Color	*Color_normalize(Color *this)
{
	float m = maxf(this->r, maxf(this->g, maxf(this->b, this->a)));

	return Color_scale(this, 1.f / m);
}

Color	*Color_trunc(Color *this)
{
	return Color_setValues(this,
		clampf(this->r, 0.f, 1.f),
		clampf(this->g, 0.f, 1.f),
		clampf(this->b, 0.f, 1.f),
		clampf(this->a, 0.f, 1.f));
}