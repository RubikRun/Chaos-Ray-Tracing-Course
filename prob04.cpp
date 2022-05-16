#include "RayTracer.h"
#include "Scene.h"

int main() {
	Scene scene;
	scene.readFromFile("scenes/scene4.crtscene");

	RayTracer rayTracer(scene);
	rayTracer.renderImage("render/04.ppm");

	return 0;
}