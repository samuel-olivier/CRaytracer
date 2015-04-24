#ifndef __RENDERER__
#define __RENDERER__

#include "Scene.h"
#include "XContext.h"
#include "Integrator.h"

typedef struct
{
	Scene		*scene;
	Integrator	*integrator;
	Image		*output;
	Color		*image;
}				Renderer;

Renderer	*Renderer_new();
void		Renderer_delete(Renderer *this);
Renderer	*Renderer_init(Renderer *this);

void		Renderer_render(Renderer *this);
void		Renderer_flushOutput(Renderer *this);

#endif