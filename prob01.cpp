#include <iostream>

#include "RayTracer.h"

int main() {
	const Image image {
		{ 1280, 720 }, // resolution
		{ 2.f, 2.f }, // size
		1.f // distToCamera
	};

	Triangle triangles[1] = {
		Triangle(
			Vec3f(-1.75f, -1.75f, -3.f),
			Vec3f(1.75f, -1.75f, -3.f),
			Vec3f(0.f, 1.75f, -3.f)
		)
	};

	const Scene scene = { triangles, 1 };

	RayTracer rayTracer(image, scene);
	if (!rayTracer.writeImage("render/output_image_01.ppm")) {
		std::cout << "Cannot write output image.\n";
	}

	return 0;
}