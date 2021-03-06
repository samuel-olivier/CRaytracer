#include "Renderer.h"

#include <stdlib.h>
#include <stdio.h>

#include "Time.h"
#include "Config.h"

static void		setPixel(Renderer *this, int sampleNumber, int x, int y, Color *shade);
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
	return this;
}

void		Renderer_render(Renderer *this)
{
	Color			fill;
	Intersection	hit;
	Ray				ray;
	Time			timer;

	Time_init(&timer);
	Color_init(&fill);
	initImage(this);
	for (int sampleNumber = 0; sampleNumber < INTEGRATOR_SAMPLE_NUMBER; ++sampleNumber) {
		for (int y = 0; y < this->output->height; ++y) {
			for (int x = 0; x < this->output->width; ++x) {
				float xF = ((float)x + 0.5f) / this->output->width;
				float yF = ((float)y + 0.5f) / this->output->height;

				Camera_ray(this->scene->camera, xF, -yF, &ray);
				ray.type = PrimaryRay;
				ray.depth = 0;

				Intersection_init(&hit);
				Integrator_compute(this->integrator, this->scene, &ray, &hit);
				Color_clamp(&hit.shade);
				setPixel(this, sampleNumber, x, y, &hit.shade);
			}
		}
		// Renderer_flushOutput(this);
		printf("Sample %d : %fs\n", sampleNumber, Time_update(&timer));
	}
}

void		Renderer_flushOutput(Renderer *this)
{
	int idx;

	for (int y = 0; y < this->output->height; ++y) {
		for (int x = 0; x < this->output->width; ++x) {
			idx = y * this->output->width + x;
			Image_putPixel(this->output, x, y, &this->image[idx]);
		}
	}
}

static void		setPixel(Renderer *this, int sampleNumber, int x, int y, Color *shade)
{
	int idx = y * this->output->width + x;
	float f = 1.0f / (sampleNumber + 1.0f);
	Color c = this->image[idx];
	Color_scale(&c, 1.0f - f);
	Color_copy(&this->image[idx], shade);
	Color_scale(&this->image[idx], f);
	Color_add(&this->image[idx], &c);
	Image_putPixel(this->output, x, y, &this->image[idx]);	
}

static void		initImage(Renderer *this)
{
	this->image = malloc(sizeof(*this->image) * this->output->height * this->output->width);

	for (int i = 0; i < this->output->height * this->output->width; ++i) {
		Color_init(&this->image[i]);
	}
}
