#include "Scene.h"
#include "Sphere.h"
#include "Mesh.h"
#include "Instance.h"
#include "LambertMaterial.h"
#include "PointLight.h"
#include "DirectionalLight.h"

Scene	*createScene1()
{
	Scene	*scene = Scene_new();

	scene->camera = Camera_new();
	Camera_setValues(scene->camera, 40.f, 1.33f);
	// Camera_setValues(scene->camera, 40.f, (float)WINDOW_WIDTH / WINDOW_HEIGHT);
	Vec3	cPosition;
	Vec3_setValues(&cPosition, 2.f, 2.f, 5.f);
	Vec3	target;
	Vec3_setValues(&target, 0.f, 0.f, 0.f);
	Vec3	up;
	Vec3_setValues(&up, 0.f, 1.f, 0.f);
	Camera_lookAt(scene->camera, &cPosition, &target, &up);

	Color_setValues(&scene->sky, 0.8f, 0.9f, 1.0f, 1.f);

	Color		cubeCol;
	Color_setValues(&cubeCol, 0.6f, 0.6f, 0.6f, 1.f);
	Material	*cubeMat = LambertMaterial_new(&cubeCol);

	Color		groundCol;
	Color_setValues(&groundCol, 0.6f, 0.6f, 0.6f, 1.f);
	Material	*groundMat = LambertMaterial_new(&groundCol);

	Object *ground = Mesh_new();
	Mesh_makeBox(ground, 5.f, 0.1f, 5.f);
	ground->material = groundMat;
	Scene_addObject(scene, ground);

	Object *box = Mesh_new();
	Mesh_makeBox(box, 1.f, 1.0f, 1.f);
	box->material = cubeMat;

	Object *inst1 = Instance_new(box);
	Mat4x4	m;
	Mat4x4_toIdentity(&m);
	Mat4x4_rotateX(&m, 0.5f);
	Vec3	tr;
	Vec3_setValues(&tr, 0.f, 1.f, 0.f);
	Mat4x4_translate(&m, &tr);
	Instance_setMatrix(inst1, &m);
	Scene_addObject(scene, inst1);

	Object *inst2 = Instance_new(box);
	Mat4x4_toIdentity(&m);
	Mat4x4_rotateY(&m, 1.f);
	Vec3_setValues(&tr, -1.f, 0.f, 1.f);
	Mat4x4_translate(&m, &tr);
	Instance_setMatrix(inst2, &m);
	Scene_addObject(scene, inst2);

	Vec3	lPos;
	Vec3_setValues(&lPos, 2.f, 2.f, 0.f);
	Color	lCol;
	Color_setValues(&lCol, 1.f, 0.2f, 0.2f, 1.f);
	Light	*redLgt = PointLight_new(&lPos, &lCol, 2.f);
	Scene_addLight(scene, redLgt);

	Vec3	lDir;
	Vec3_setValues(&lDir, -0.5f, -1.f, -0.5f);
	Color_setValues(&lCol, 1.f, 1.f, 0.9f, 1.f);
	Light	*sunLgt = DirectionalLight_new(&lDir, &lCol, 0.5f);
	Scene_addLight(scene, sunLgt);

	return scene;
}