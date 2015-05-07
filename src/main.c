
#include <unistd.h>
#include <math.h>

#include "XContext.h"
#include "Renderer.h"
#include "Thread.h"
#include "Config.h"

Scene	*createScene1();
Scene	*createScene2();

void	threadRendering(void *params)
{
	Renderer_render(params);
}

int	main()
{
	XContext	*mlx = XContext_new();
	Thread		*renderingThread = Thread_new(); 

	XContext_createWindow(mlx, WINDOW_WIDTH, WINDOW_HEIGHT, "Raytracer");
	Renderer *renderer = Renderer_new();
	renderer->output = mlx->displayImage;
	renderer->scene = createScene2();
	renderer->integrator = Integrator_new(INTEGRATOR);
	Thread_run(renderingThread, &threadRendering, renderer);
	XContext_displayLoop(mlx, 30, NULL, NULL);
	Thread_join(renderingThread);
  	return 0;
}
