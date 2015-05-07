#include "Scene.h"
#include "Sphere.h"
#include "Mesh.h"
#include "Instance.h"
#include "LambertMaterial.h"
#include "PointLight.h"
#include "DirectionalLight.h"
#include "AreaLight.h"
#include "Config.h"
#include "Utils.h"

Scene	*createScene2()
{
	Scene	*scene = Scene_new();

	scene->camera = Camera_new();
	Camera_setValues(scene->camera, 40.f, (float)WINDOW_WIDTH / WINDOW_HEIGHT);
	Vec3	cPosition;
	Vec3_setValues(&cPosition, 0.f, 0.75f, 3.f);
	Vec3	target;
	Vec3_setValues(&target, 0.f, 0.75f, 0.f);
	Vec3	up;
	Vec3_setValues(&up, 0.f, 1.f, 0.f);
	Camera_lookAt(scene->camera, &cPosition, &target, &up);

	Color_setValues(&scene->sky, 0.0f, 0.0f, 0.0f, 1.f);

	Color		lWallCol;
	Color_setValues(&lWallCol, 0.63f, 0.065f, 0.05f, 1.f);
	Material	*lWallMat = LambertMaterial_new(&lWallCol);

	Color		rWallCol;
	Color_setValues(&rWallCol, 0.161f, 0.133f, 0.427f, 1.f);
	Material	*rWallMat = LambertMaterial_new(&rWallCol);

	Color		oWallCol;
	Color_setValues(&oWallCol, 0.725f, 0.71f, 0.68f, 1.f);
	Material	*oWallMat = LambertMaterial_new(&oWallCol);

	Object *wall = Mesh_new();
	Mesh_makeRectangle(wall, 2.f, 2.f);

	Object *lightMesh = Mesh_new();
	Mesh_makeRectangle(lightMesh, 0.47f, 0.38f);

	Mat4x4	m;
	Vec3	tr;

	Object *ground = Instance_new(wall);
	Mat4x4_toIdentity(&m);
	Mat4x4_rotateX(&m, M_PI / 2.f);
	Instance_setMatrix(ground, &m);
	ground->material = oWallMat;
	Scene_addObject(scene, ground);

	Object *ceiling = Instance_new(wall);
	Mat4x4_toIdentity(&m);
	Mat4x4_rotateX(&m, M_PI / 2.f);
	Vec3_setValues(&tr, 0.f, 1.6f, 0.f);
	Mat4x4_translate(&m, &tr);
	Instance_setMatrix(ceiling, &m);
	ceiling->material = oWallMat;
	Scene_addObject(scene, ceiling);

	Object *back = Instance_new(wall);
	Mat4x4_toIdentity(&m);
	Vec3_setValues(&tr, 0.f, 0.8f, -1.f);
	Mat4x4_translate(&m, &tr);
	Instance_setMatrix(back, &m);
	back->material = oWallMat;
	Scene_addObject(scene, back);

	Object *left = Instance_new(wall);
	Mat4x4_toIdentity(&m);
	Mat4x4_rotateY(&m, M_PI / 2.f);
	Vec3_setValues(&tr, -1.f, 0.8f, 0.f);
	Mat4x4_translate(&m, &tr);
	Instance_setMatrix(left, &m);
	left->material = lWallMat;
	Scene_addObject(scene, left);

	Object *right = Instance_new(wall);
	Mat4x4_toIdentity(&m);
	Mat4x4_rotateY(&m, M_PI / 2.f);
	Vec3_setValues(&tr, 1.f, 0.8f, 0.f);
	Mat4x4_translate(&m, &tr);
	Instance_setMatrix(right, &m);
	right->material = rWallMat;
	Scene_addObject(scene, right);

	Object *lightInst = Instance_new(lightMesh);
	Mat4x4_toIdentity(&m);
	Mat4x4_rotateX(&m, M_PI / 2.f);
	Vec3_setValues(&tr, 0.f, 1.59f, 0.f);
	Mat4x4_translate(&m, &tr);
	Instance_setMatrix(lightInst, &m);
	lightInst->material = NULL;
	Scene_addObject(scene, lightInst);

	Vec3	lSphPos;
	Vec3_setValues(&lSphPos, -0.4214f, 0.325f, -0.28f);
	Object	*lSph = Sphere_new(&lSphPos, 0.325);
	lSph->material = oWallMat;
	Scene_addObject(scene, lSph);

	Vec3	rSphPos;
	Vec3_setValues(&rSphPos, 0.4458f, 0.325f, 0.37675f);
	Object	*rSph = Sphere_new(&rSphPos, 0.325);
	rSph->material = oWallMat;
	Scene_addObject(scene, rSph);

	Vec3	lPos;
	Vec3_setValues(&lPos, -0.24f, 1.58f, -0.22f);
	Vec3	lU;
	Vec3_setValues(&lU, 0.47f, 0.f, 0.f);
	Vec3	lV;
	Vec3_setValues(&lV, 0.f, 0.f, 0.38f);
	Color	lCol;
	Color_setValues(&lCol, 1.f, 1.0f, 1.0f, 1.f);
	Light	*light = AreaLight_new(&lCol, 2.f);
	AreaLight_makeRectangle(light, &lPos, &lU, &lV);
	lightInst->light = light;
	Scene_addLight(scene, light);
	return scene;
}
