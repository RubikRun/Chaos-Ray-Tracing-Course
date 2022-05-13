#include <iostream>

#include "RayTracer.h"

Scene getRotatingCubeScene(float angle, const Vec3f &offset) {
	const float pi = float(M_PI);

	Triangle *triangles = new Triangle[12] {
		// front, bottom-left
		Triangle(
			Vec3f(cosf(0.75f * pi + angle), -1.f, sinf(0.75f * pi + angle)),
			Vec3f(cosf(0.25f * pi + angle), -1.f, sinf(0.25f * pi + angle)),
			Vec3f(cosf(0.75f * pi + angle), 1.f, sinf(0.75f * pi + angle)),
			Color(200, 200, 200)
		),
		// front, top-right
		Triangle(
			Vec3f(cosf(0.25f * pi + angle), -1.f, sinf(0.25f * pi + angle)),
			Vec3f(cosf(0.25f * pi + angle), 1.f, sinf(0.25f * pi + angle)),
			Vec3f(cosf(0.75f * pi + angle), 1.f, sinf(0.75f * pi + angle)),
			Color(200, 200, 200)
		),
		// back, bottom-left
		Triangle(
			Vec3f(cosf(-0.25f * pi + angle), -1.f, sinf(-0.25f * pi + angle)),
			Vec3f(cosf(-0.75f * pi + angle), -1.f, sinf(-0.75f * pi + angle)),
			Vec3f(cosf(-0.25f * pi + angle), 1.f, sinf(-0.25f * pi + angle)),
			Color(200, 200, 20)
		),
		// back, top-right
		Triangle(
			Vec3f(cosf(-0.75f * pi + angle), -1.f, sinf(-0.75f * pi + angle)),
			Vec3f(cosf(-0.75f * pi + angle), 1.f, sinf(-0.75f * pi + angle)),
			Vec3f(cosf(-0.25f * pi + angle), 1.f, sinf(-0.25f * pi + angle)),
			Color(200, 200, 20)
		),
		// left, bottom-left
		Triangle(
			Vec3f(cosf(-0.75f * pi + angle), -1.f, sinf(-0.75f * pi + angle)),
			Vec3f(cosf(0.75f * pi + angle), -1.f, sinf(0.75f * pi + angle)),
			Vec3f(cosf(-0.75f * pi + angle), 1.f, sinf(-0.75f * pi + angle)),
			Color(10, 10, 200)
		),
		// left, top-right
		Triangle(
			Vec3f(cosf(0.75f * pi + angle), -1.f, sinf(0.75f * pi + angle)),
			Vec3f(cosf(0.75f * pi + angle), 1.f, sinf(0.75f * pi + angle)),
			Vec3f(cosf(-0.75f * pi + angle), 1.f, sinf(-0.75f * pi + angle)),
			Color(10, 10, 200)
		),
		// right, bottom-left
		Triangle(
			Vec3f(cosf(0.25f * pi + angle), -1.f, sinf(0.25f * pi + angle)),
			Vec3f(cosf(-0.25f * pi + angle), -1.f, sinf(-0.25f * pi + angle)),
			Vec3f(cosf(0.25f * pi + angle), 1.f, sinf(0.25f * pi + angle)),
			Color(10, 200, 10)
		),
		// right, top-right
		Triangle(
			Vec3f(cosf(-0.25f * pi + angle), -1.f, sinf(-0.25f * pi + angle)),
			Vec3f(cosf(-0.25f * pi + angle), 1.f, sinf(-0.25f * pi + angle)),
			Vec3f(cosf(0.25f * pi + angle), 1.f, sinf(0.25f * pi + angle)),
			Color(10, 200, 10)
		),
		// bottom, bottom-left
		Triangle(
			Vec3f(cosf(-0.75f * pi + angle), -1.f, sinf(-0.75f * pi + angle)),
			Vec3f(cosf(-0.25f * pi + angle), -1.f, sinf(-0.25f * pi + angle)),
			Vec3f(cosf(0.75f * pi + angle), -1.f, sinf(0.75f * pi + angle)),
			Color(200, 120, 10)
		),
		// bottom, top-right
		Triangle(
			Vec3f(cosf(-0.25f * pi + angle), -1.f, sinf(-0.25f * pi + angle)),
			Vec3f(cosf(0.25f * pi + angle), -1.f, sinf(0.25f * pi + angle)),
			Vec3f(cosf(0.75f * pi + angle), -1.f, sinf(0.75f * pi + angle)),
			Color(200, 120, 10)
		),
		// top, bottom-left
		Triangle(
			Vec3f(cosf(0.75f * pi + angle), 1.f, sinf(0.75f * pi + angle)),
			Vec3f(cosf(0.25f * pi + angle), 1.f, sinf(0.25f * pi + angle)),
			Vec3f(cosf(-0.75f * pi + angle), 1.f, sinf(-0.75f * pi + angle)),
			Color(200, 10, 10)
		),
		// top, top-right
		Triangle(
			Vec3f(cosf(0.25f * pi + angle), 1.f, sinf(0.25f * pi + angle)),
			Vec3f(cosf(-0.25f * pi + angle), 1.f, sinf(-0.25f * pi + angle)),
			Vec3f(cosf(-0.75f * pi + angle), 1.f, sinf(-0.75f * pi + angle)),
			Color(200, 200, 10)
		)
	};

	for (int trIdx = 0; trIdx < 12; trIdx++) {
		for (int vIdx = 0; vIdx < 3; vIdx++) {
			triangles[trIdx].vertices[vIdx] += offset;
		}
	}

	return { triangles, 12 };
}

int main() {
	const Image image {
		{ 600, 600 }, // resolution
		{ 2.f, 2.f }, // size
		2.f // distToCamera
	};

	const int framesCount = 300;

	const float firstAngle = 0.f;
	const float lastAngle = 4.f * M_PI;
	const float deltaAngle = (lastAngle - firstAngle) / float(framesCount - 1);

	int frame = 0;
	for (float angle = firstAngle; angle <= lastAngle; angle += deltaAngle) {
		std::cout << "Rendering frame " << frame << ".\n";
		const Scene scene = getRotatingCubeScene(angle, { 0.f, 0.f, -3.5f });

		const std::string filepath = std::string("anim/") + getStringFromNumber(frame, 4) + ".ppm";
		RayTracer rayTracer(image, scene);
		if (!rayTracer.writeImage(filepath.c_str())) {
			std::cout << "Cannot write output image.\n";
		}
		frame++;
	}

	return 0;
}