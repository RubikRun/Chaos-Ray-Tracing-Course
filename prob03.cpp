#include <iostream>

#include "RayTracer.h"

int main() {
	const Image image {
		{ 1280, 720 }, // resolution
		{ 2.f, 2.f }, // size
		1.f // distToCamera
	};

	Triangle triangles[3] = {
		Triangle(
			Vec3f(-1.75f, -1.75f, -3.5f),
			Vec3f(1.75f, -1.75f, -3.5f),
			Vec3f(0.f, 1.75f, -2.7f),
			Color(255, 0, 0)
		),
		Triangle(
			Vec3f(-1.f, 0.f, -3.f),
			Vec3f(1.f, 0.f, -3.f),
			Vec3f(-1.f, 2.f, -3.f),
			Color(40, 100, 180)
		),
		Triangle(
			Vec3f(1.6f, 1.6f, -3.f),
			Vec3f(1.8f, 1.65f, -3.f),
			Vec3f(1.5f, 1.9, -3.f),
			Color(0, 255, 255)
		)
	};

	const Scene scene = { triangles, 3 };

	RayTracer rayTracer(image, scene);
	if (!rayTracer.writeImage("render/output_image_03.ppm")) {
		std::cout << "Cannot write output image.\n";
	}

	return 0;
}