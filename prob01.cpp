#include "RayTracer.h"

int main() {
	Image image {
		{ 1280, 720 }, // resolution
		{ 5.f, 5.f }, // size
		2.f // distToCamera
	};

	RayTracer rayTracer(image);
	rayTracer.writeImage("output_image_01.ppm");

	return 0;
}