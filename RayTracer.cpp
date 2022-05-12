#include "RayTracer.h"

#include <fstream>

static const int maxColorComponent = 255;

RayTracer::RayTracer(const Image &image)
	: image(image)
{
	if (image.resolution.x > 0 && image.resolution.y > 0) {
		rays = new Ray[image.getPixelCount()];
		generateRays();
	}
}

RayTracer::~RayTracer() {
	delete[] rays;
}

bool RayTracer::writeImage(const char *filepath) const {
	// Open stream to the output file
	std::ofstream ppmFileStream(filepath, std::ios::out | std::ios::binary);
	if (!ppmFileStream.is_open()) {
		return false;
	}
	// Write PPM metadata about PPM version, image resolution and max color component
    ppmFileStream << "P3\n";
    ppmFileStream << image.resolution.x << " " << image.resolution.y << "\n";
    ppmFileStream << maxColorComponent << "\n";

    // Traverse pixels of the image
    for (Vec2i pixel = { 0, 0 }; pixel.y < image.resolution.y; pixel.y++) {
		for (pixel.x = 0; pixel.x < image.resolution.x; pixel.x++) {
			// Index of the ray in the array that corresponds to this pixel
			const int rayIdx = pixel.y * image.resolution.x + pixel.x;
			// Use the ray's color to color the pixel
			const Color color = rays[rayIdx].color;
			// Write the color to the output image file for the current pixel
			ppmFileStream << color.r << " " << color.g << " " << color.b << "\t";
		}
		ppmFileStream << "\n";
	}

    ppmFileStream.close();

    return true;
}

void RayTracer::generateRays() {
	// Traverse pixels of the image
	for (Vec2i pixel = { 0, 0 }; pixel.y < image.resolution.y; pixel.y++) {
		for (pixel.x = 0; pixel.x < image.resolution.x; pixel.x++) {
			// Index of the ray in the array that corresponds to this pixel
			const int rayIdx = pixel.y * image.resolution.x + pixel.x;
			// Generate a ray for this pixel and save it in the rays array
			rays[rayIdx] = generateRay(pixel);
		}
	}
}

Ray RayTracer::generateRay(const Vec2i &pixel) const {
	Ray ray;

	const Vec2f pixelCenter = {
		float(pixel.x) + 0.5f,
		float(pixel.y) + 0.5f
	};

	const Vec2f ndcPoint = {
		pixelCenter.x / float(image.resolution.x),
		pixelCenter.y / float(image.resolution.y)
	};

	const Vec2f screenPoint = {
		ndcPoint.x * 2.f - 1.f,
		1.f - ndcPoint.y * 2.f
	};

	const Vec2f worldPoint = {
		screenPoint.x * image.size.x * 0.5f,
		screenPoint.y * image.size.y * 0.5f
	};

	const Vec3f cameraToPixel = {
		worldPoint.x,
		worldPoint.y,
		-image.distToCamera
	};

	ray.orig = { 0.f, 0.f, 0.f };
	ray.dir = cameraToPixel.getNormal();
	ray.pixel = pixel;
	ray.color = {
		int((ray.dir.x + 1.f) * 0.5f * float(maxColorComponent)),
		int((ray.dir.y + 1.f) * 0.5f * float(maxColorComponent)),
		int((ray.dir.z + 1.f) * 0.5f * float(maxColorComponent))
	};

	return ray;
}