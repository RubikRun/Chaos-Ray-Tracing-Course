#include "RayTracer.h"
#include "Scene.h"

int main() {
	Scene scene;
	scene.readFromFile("scenes/scene1.crtscene");

	RayTracer rayTracer(scene);
	rayTracer.renderImage("render/01.ppm");

	return 0;
}