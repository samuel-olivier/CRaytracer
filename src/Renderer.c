#include "Renderer.h"

#include <stdlib.h>

static void		setPixel(Renderer *this, int x, int y, Color *shade);
static void		initImage(Renderer *this);

Renderer	*Renderer_new()
{
	return Renderer_init(malloc(sizeof(Renderer)));
}

void		Renderer_delete(Renderer *this)
{
	free(this);
}

Renderer	*Renderer_init(Renderer *this)
{
	this->scene = NULL;
	this->integrator = NULL;
	this->output = NULL;
}

void		Renderer_render(Renderer *this)
{
	Color			fill;
	Intersection	hit;
	Ray				ray;

	Color_init(&fill);
	initImage
	for (int y = 0; y < this->output->height; ++y) {
		for (int x = 0; x < this->output->width; ++x) {
			Camera_ray(this->scene->camera, (float)x + 0.5f, -(float)y + 0.5f, ray);
			ray.type = Primary;
			ray.depth = 0;

			Intersection_init(&hit);
            Integrator_compute(this->integrator, &ray, &hit);
            setPixel(this, x, y, &hit.color);
        }
	}
}

void		Renderer_flushOutput(Renderer *this);

static void		setPixel(Renderer *this, int sampleNumber, int x, int y, Color *shade)
{
	int i = y * this->output->width + x;
    float f = 1.0f / (sampleNumber + 1.0f);
    Color c = _imageColors[idx];
    c.Scale(1.0f - f);
    c.AddScaled(color, f);
    _imageColors[idx] = c;
    _image.setPixel(x, y, c.ToInt());	Color_scale(&this->image[i], sampleNumber);
	Color_scale()
}

static void		initImage(Renderer *this)
{
	this->image = malloc(sizeof(*this->image) * this->output->height * this->output->width);

	for (int i = 0; i < this->output->height * this->output->width; ++i) {
		Color_init(&this->image[i]);
	}
}
