#ifndef __RENDERER__
#define __RENDERER__

#include 

typedef struct
{
	Scene		*scene;
	XContext	*context;
	Integrator	*integrator;
}				Renderer;

Renderer	*Renderer_new();
void		Renderer_delete(Renderer *this);
Renderer	*Renderer_init(Renderer *this);

#endif