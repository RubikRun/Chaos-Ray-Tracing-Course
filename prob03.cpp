#include "RayTracer.h"
#include "Scene.h"

int main() {
	Scene scene;
	scene.readFromFile("scenes/scene3.crtscene");

	RayTracer rayTracer(scene);
	rayTracer.renderImage("render/03.ppm");

	return 0;
}