#include "RayTracer.h"
#include "Scene.h"

int main() {
	Scene scene;
	scene.readFromFile("scenes/scene2.crtscene");

	RayTracer rayTracer(scene);
	rayTracer.renderImage("render/02.ppm");

	return 0;
}