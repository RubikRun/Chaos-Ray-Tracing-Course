#include "RayTracer.h"
#include "Scene.h"

int main() {
	Scene scene;
	scene.readFromFile("scenes/scene0.crtscene");

	RayTracer rayTracer(scene);
	rayTracer.renderImage("render/00.ppm");

	return 0;
}