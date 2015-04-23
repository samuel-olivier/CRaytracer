
#include <unistd.h>
#include <math.h>

#include "XContext.h"
#include "Sphere.h"

int	main()
{
	XContext *mlx = XContext_new();
	Color	*color = Color_new();
	float		i = 0;

	Object	*s = Sphere_new(Vec3_create(1.f, 2.f, 3.f), 5);
	Object_intersect(s, NULL, NULL);

	XContext_createWindow(mlx, 800, 600, "Raytracer");
	while (1) {
		color->r = sin(i);
		Image_fill(mlx->displayImage, color);
		i += 0.01;
		XContext_display(mlx);
		usleep(33000);
	}
  	return 0;
}
