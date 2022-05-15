#include <iostream>

#include "RayTracer.h"

void getRotatingCube(float angle, const Vec3f &offset, Triangle *triangles, int &trianglesCount) {
	const float pi = float(M_PI);
	const float sqrt2 = sqrtf(2.f);

	// front, bottom-left
	triangles[trianglesCount++] = Triangle(
		Vec3f(sqrt2 * cosf(0.75f * pi + angle), -1.f, sqrt2 * sinf(0.75f * pi + angle)) + offset,
		Vec3f(sqrt2 * cosf(0.25f * pi + angle), -1.f, sqrt2 * sinf(0.25f * pi + angle)) + offset,
		Vec3f(sqrt2 * cosf(0.75f * pi + angle), 1.f, sqrt2 * sinf(0.75f * pi + angle)) + offset,
		Color(200, 200, 200)
	);
	// front, top-right
	triangles[trianglesCount++] = Triangle(
		Vec3f(sqrt2 * cosf(0.25f * pi + angle), -1.f, sqrt2 * sinf(0.25f * pi + angle)) + offset,
		Vec3f(sqrt2 * cosf(0.25f * pi + angle), 1.f, sqrt2 * sinf(0.25f * pi + angle)) + offset,
		Vec3f(sqrt2 * cosf(0.75f * pi + angle), 1.f, sqrt2 * sinf(0.75f * pi + angle)) + offset,
		Color(200, 200, 200)
	);
	// back, bottom-left
	triangles[trianglesCount++] = Triangle(
		Vec3f(sqrt2 * cosf(-0.25f * pi + angle), -1.f, sqrt2 * sinf(-0.25f * pi + angle)) + offset,
		Vec3f(sqrt2 * cosf(-0.75f * pi + angle), -1.f, sqrt2 * sinf(-0.75f * pi + angle)) + offset,
		Vec3f(sqrt2 * cosf(-0.25f * pi + angle), 1.f, sqrt2 * sinf(-0.25f * pi + angle)) + offset,
		Color(200, 200, 20)
	);
	// back, top-right
	triangles[trianglesCount++] = Triangle(
		Vec3f(sqrt2 * cosf(-0.75f * pi + angle), -1.f, sqrt2 * sinf(-0.75f * pi + angle)) + offset,
		Vec3f(sqrt2 * cosf(-0.75f * pi + angle), 1.f, sqrt2 * sinf(-0.75f * pi + angle)) + offset,
		Vec3f(sqrt2 * cosf(-0.25f * pi + angle), 1.f, sqrt2 * sinf(-0.25f * pi + angle)) + offset,
		Color(200, 200, 20)
	);
	// left, bottom-left
	triangles[trianglesCount++] = Triangle(
		Vec3f(sqrt2 * cosf(-0.75f * pi + angle), -1.f, sqrt2 * sinf(-0.75f * pi + angle)) + offset,
		Vec3f(sqrt2 * cosf(0.75f * pi + angle), -1.f, sqrt2 * sinf(0.75f * pi + angle)) + offset,
		Vec3f(sqrt2 * cosf(-0.75f * pi + angle), 1.f, sqrt2 * sinf(-0.75f * pi + angle)) + offset,
		Color(10, 10, 200)
	);
	// left, top-right
	triangles[trianglesCount++] = Triangle(
		Vec3f(sqrt2 * cosf(0.75f * pi + angle), -1.f, sqrt2 * sinf(0.75f * pi + angle)) + offset,
		Vec3f(sqrt2 * cosf(0.75f * pi + angle), 1.f, sqrt2 * sinf(0.75f * pi + angle)) + offset,
		Vec3f(sqrt2 * cosf(-0.75f * pi + angle), 1.f, sqrt2 * sinf(-0.75f * pi + angle)) + offset,
		Color(10, 10, 200)
	);
	// right, bottom-left
	triangles[trianglesCount++] = Triangle(
		Vec3f(sqrt2 * cosf(0.25f * pi + angle), -1.f, sqrt2 * sinf(0.25f * pi + angle)) + offset,
		Vec3f(sqrt2 * cosf(-0.25f * pi + angle), -1.f, sqrt2 * sinf(-0.25f * pi + angle)) + offset,
		Vec3f(sqrt2 * cosf(0.25f * pi + angle), 1.f, sqrt2 * sinf(0.25f * pi + angle)) + offset,
		Color(10, 200, 10)
	);
	// right, top-right
	triangles[trianglesCount++] = Triangle(
		Vec3f(sqrt2 * cosf(-0.25f * pi + angle), -1.f, sqrt2 * sinf(-0.25f * pi + angle)) + offset,
		Vec3f(sqrt2 * cosf(-0.25f * pi + angle), 1.f, sqrt2 * sinf(-0.25f * pi + angle)) + offset,
		Vec3f(sqrt2 * cosf(0.25f * pi + angle), 1.f, sqrt2 * sinf(0.25f * pi + angle)) + offset,
		Color(10, 200, 10)
	);
	// bottom, bottom-left
	triangles[trianglesCount++] = Triangle(
		Vec3f(sqrt2 * cosf(-0.75f * pi + angle), -1.f, sqrt2 * sinf(-0.75f * pi + angle)) + offset,
		Vec3f(sqrt2 * cosf(-0.25f * pi + angle), -1.f, sqrt2 * sinf(-0.25f * pi + angle)) + offset,
		Vec3f(sqrt2 * cosf(0.75f * pi + angle), -1.f, sqrt2 * sinf(0.75f * pi + angle)) + offset,
		Color(200, 120, 10)
	);
	// bottom, top-right
	triangles[trianglesCount++] = Triangle(
		Vec3f(sqrt2 * cosf(-0.25f * pi + angle), -1.f, sqrt2 * sinf(-0.25f * pi + angle)) + offset,
		Vec3f(sqrt2 * cosf(0.25f * pi + angle), -1.f, sqrt2 * sinf(0.25f * pi + angle)) + offset,
		Vec3f(sqrt2 * cosf(0.75f * pi + angle), -1.f, sqrt2 * sinf(0.75f * pi + angle)) + offset,
		Color(200, 120, 10)
	);
	// top, bottom-left
	triangles[trianglesCount++] = Triangle(
		Vec3f(sqrt2 * cosf(0.75f * pi + angle), 1.f, sqrt2 * sinf(0.75f * pi + angle)) + offset,
		Vec3f(sqrt2 * cosf(0.25f * pi + angle), 1.f, sqrt2 * sinf(0.25f * pi + angle)) + offset,
		Vec3f(sqrt2 * cosf(-0.75f * pi + angle), 1.f, sqrt2 * sinf(-0.75f * pi + angle)) + offset,
		Color(200, 20, 10)
	);
	// top, top-right
	triangles[trianglesCount++] = Triangle(
		Vec3f(sqrt2 * cosf(0.25f * pi + angle), 1.f, sqrt2 * sinf(0.25f * pi + angle)) + offset,
		Vec3f(sqrt2 * cosf(-0.25f * pi + angle), 1.f, sqrt2 * sinf(-0.25f * pi + angle)) + offset,
		Vec3f(sqrt2 * cosf(-0.75f * pi + angle), 1.f, sqrt2 * sinf(-0.75f * pi + angle)) + offset,
		Color(200, 20, 10)
	);
}

Scene getRotatingCubesScene(float angle, float offset, const Vec2i cubesCount) {
	const int trTotalCount = (cubesCount.x * 2 + 1) * (cubesCount.y * 2 + 1) * 12;
	Triangle *triangles = new Triangle[trTotalCount];
	int trFilled = 0;

	for (int xIdx = -cubesCount.x; xIdx <= cubesCount.x; xIdx++) {
		for (int yIdx = -cubesCount.y; yIdx <= cubesCount.y; yIdx++) {
			getRotatingCube(angle, { float(xIdx) * offset, 0.f, float(yIdx) * offset }, triangles, trFilled);
		}
	}

	return { triangles, trTotalCount };
}

int main() {
	const float imageRatio = 1080.f / 1920.f;

	const Vec2i imageResolution = {
		1000,
		int(1000 * imageRatio) 
	};

	Camera camera(		
		{ 2.f, 2.f * imageRatio },
		2.f
	);
	camera.position = { 0.f, 0.f, 25.f };

	const int framesCount = 200;

	const float firstAngle = 0.f;
	const float lastAngle = 2 * M_PI;
	const float deltaAngle = (lastAngle - firstAngle) / float(framesCount - 1);

	int frame = 0;
	for (float angle = firstAngle; angle <= lastAngle; angle += deltaAngle) {
		std::cout << "Rendering frame " << frame << ".\n";
		const std::string filepath = std::string("anim/") + getStringFromNumber(frame, 4) + ".ppm";

		const Scene scene = getRotatingCubesScene(angle * 8.f, 7.f, { 2, 2 });

		RayTracer rayTracer(camera, imageResolution);
		rayTracer.setScene(scene);
		if (!rayTracer.renderImage(filepath.c_str())) {
			std::cout << "Cannot write output image.\n";
		}

		frame++;

		camera.boom(tanf(deltaAngle) * camera.position.getLength());
		camera.tilt(-deltaAngle);

		camera.truck(tanf(deltaAngle) * camera.position.getLength());
		camera.pan(-deltaAngle);

		camera.dolly(-0.4f);

		delete[] scene.triangles;
	}

	return 0;
}