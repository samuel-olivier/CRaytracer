#ifndef __IMAGE__
#define __IMAGE__

#include "Color.h"

struct sXContext;

typedef struct 
{
	void			*mlxData;
	unsigned char	*bytes;
	int				width;
	int				height;
	int				bpp;
	int				sizeLine;
	int				endian;
}					Image;

Image	*Image_new(struct sXContext *context, int width, int height);
void	Image_delete(Image *this);

void	Image_putPixel(Image *this, int x, int y, Color *color);
void	Image_fill(Image *this, Color *color);

void	Image_putToWindow(Image *this, struct sXContext *context, int x, int y);

#endif