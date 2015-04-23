#include "Image.h"

#include <stdlib.h>
#include <mlx.h>

#include "XContext.h"

Image	*Image_new(XContext *context, int width, int height)
{
	if (width <= 0 || height <= 0) {
		return NULL;
	}
	Image	*this = malloc(sizeof(*this));

	this->mlxData = mlx_new_image(context->server, width, height);
	if (this->mlxData == NULL) {
		free(this);
		return NULL;
	}
	this->bytes = (unsigned char*)mlx_get_data_addr(this->mlxData,
		&this->bpp,
		&this->sizeLine,
		&this->endian);
	this->width = width;
	this->height = height;	
	return this;
}

void	Image_delete(Image *this)
{
	free(this);
}

void	Image_putPixel(Image *this, int x, int y, Color *color)
{
	if (x < 0 || x >= this->width || y < 0 || y >= this->height) {
		return ;
	}
	int idx = y * this->sizeLine + x * this->bpp / 8;
	this->bytes[idx + 0] = (char)(color->b * 255.f);
	this->bytes[idx + 1] = (char)(color->g * 255.f);
	this->bytes[idx + 2] = (char)(color->r * 255.f);
	this->bytes[idx + 3] = 255;
}

void	Image_fill(Image *this, Color *color)
{
	for (int y = 0; y < this->height; ++y) {
		for (int x = 0; x < this->width; ++x) {
			Image_putPixel(this, x, y, color);
		}
	}
}


void	Image_putToWindow(Image *this, XContext *context, int x, int y)
{
	if (x < 0 || y < 0) {
		return ;
	}
	mlx_put_image_to_window(context->server, context->window, this->mlxData, x, y);
}
