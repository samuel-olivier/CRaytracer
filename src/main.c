
#include <unistd.h>
#include <math.h>

#include "XContext.h"
#include "Renderer.h"
#include "Sphere.h"
#include "Mesh.h"
#include "LambertMaterial.h"
#include "PointLight.h"

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 450

Scene	*createScene()
{
	Scene	*scene = Scene_new();

	scene->camera = Camera_new();
	Camera_setValues(scene->camera, 40.f, (float)WINDOW_WIDTH / WINDOW_HEIGHT);
	Vec3	cPosition;
	Vec3_setValues(&cPosition, -1.5f, 1.5f, 2.f);
	Vec3	target;
	Vec3_setValues(&target, 0.f, 0.f, -1.f);
	Vec3	up;
	Vec3_setValues(&up, 0.f, 1.f, 0.f);
	Camera_lookAt(scene->camera, &cPosition, &target, &up);


	Vec3	sPosition;
	Object *sph = Sphere_new(Vec3_init(&sPosition), 0.5f);
	Color		sCol;
	Color_setValues(&sCol, 0.95f, 0.0f, 0.0f, 1.f);
	Material	*sMat = LambertMaterial_new(&sCol);
	sph->material = sMat;
	Scene_addObject(scene, sph);

	Object *bPlane = Mesh_new();
	Mesh_makeRectangle(bPlane, (Vec3[4]){
		{-1.f, -1.f, -1.f},
		{-1.f, 1.f, -1.f},
		{1.f, 1.f, -1.f},
		{1.f, -1.f, -1.f}
	});
	Color		bpCol;
	Color_setValues(&bpCol, 0.f, 0.95f, 0.f, 1.f);
	Material	*bpMat = LambertMaterial_new(&bpCol);
	bPlane->material = bpMat;
	Scene_addObject(scene, bPlane);

	Vec3	lPos;
	Vec3_setValues(&lPos, 0.0f, 0.f, 2.f);
	Color	lCol;
	Color_setValues(&lCol, 1.f, 1.f, 1.f, 1.f);
	Light	*lgt = PointLight_new(&lPos, &lCol, 3.0f);
	Scene_addLight(scene, lgt);

	return scene;
}

int	main()
{
	XContext *mlx = XContext_new();

	XContext_createWindow(mlx, WINDOW_WIDTH, WINDOW_HEIGHT, "Raytracer");
	Renderer *renderer = Renderer_new();
	renderer->output = mlx->displayImage;
	renderer->scene = createScene();
	renderer->integrator = Integrator_new(Raytracing);
	Renderer_render(renderer, mlx);
	pause();
  	return 0;
}
