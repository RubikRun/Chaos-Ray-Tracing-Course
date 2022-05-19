#include "RayTracer.h"

#include <fstream>
#include <cmath>

static const int maxColorComponent = 255;

RayTracer::RayTracer(const Scene &scene)
	: scene(scene)
{
	if (scene.imageResolution.x > 0 && scene.imageResolution.y > 0) {
		const int totalPixels = scene.imageResolution.x * scene.imageResolution.y;

		rays = new Ray[totalPixels];
		generateRays();
	}
}

RayTracer::~RayTracer() {
	delete[] rays;
}

bool RayTracer::renderImage(const char *filepath) const {
	if (!rays) {
		return false;
	}

	const int totalPixels = scene.imageResolution.x * scene.imageResolution.y;
	pixels = new Color[totalPixels];
	traceRays();

	return writePixelsToFile(filepath);
}

void RayTracer::generateRays() const {
	// Traverse pixels of the image
	for (Vec2i pixel = { 0, 0 }; pixel.y < scene.imageResolution.y; pixel.y++) {
		for (pixel.x = 0; pixel.x < scene.imageResolution.x; pixel.x++) {
			// Index of the ray in the rays array - same as the pixel index
			const int rayIdx = pixel.y * scene.imageResolution.x + pixel.x;
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
		pixelCenter.x / float(scene.imageResolution.x),
		pixelCenter.y / float(scene.imageResolution.y)
	};

	const Vec2f screenPoint = {
		ndcPoint.x * 2.f - 1.f,
		1.f - ndcPoint.y * 2.f
	};

	const Vec2f worldPoint = {
		screenPoint.x * scene.camera.viewSize.x * 0.5f,
		screenPoint.y * scene.camera.viewSize.y * 0.5f
	};

	const Vec3f cameraToPixel = {
		worldPoint.x,
		worldPoint.y,
		-scene.camera.viewDepth
	};

	ray.origin = scene.camera.position;
	ray.direction = scene.camera.rotation * cameraToPixel.getNormal();

	return ray;
}

void RayTracer::traceRays() const {
	// Traverse rays
	for (int rayIdx = 0; rayIdx < scene.imageResolution.x * scene.imageResolution.y; rayIdx++) {
		// Trace each ray and save the calculated color to the corresponding pixel in the pixels array
		pixels[rayIdx] = traceRay(rays[rayIdx]);
	}
}

Color RayTracer::traceRay(const Ray &ray) const {
	// Find the closest intersection of a triangle with the ray
	TriangleIntersection closestIntersection;
	float minDist = -1.f;
	// Traverse all objects in the scene
	for (int objIdx = 0; objIdx < scene.objectsCount; objIdx++) {
		const Mesh &obj = scene.objects[objIdx];
		// Traverse all triangles of the object
		for (int trIdx = 0; trIdx < obj.trianglesCount; trIdx++) {
			// Check for an intersection between the ray and the current triangle.
			const RayTriangleIntersectionResult intersectionResult = rayTriangleIntersection(
				ray,
				obj.vertices[obj.triangles[trIdx].x],
				obj.vertices[obj.triangles[trIdx].y],
				obj.vertices[obj.triangles[trIdx].z]
			);
			// Here we are considering only intersections through the front side of the triangle
			if (!intersectionResult.doesIntersect || !intersectionResult.frontSide) {
				continue;
			}
			// If this is the first intersection found,
			// or it is closer than the currently closest,
			// than update the closest with the current one.
			if (minDist == -1 || intersectionResult.distAlongRay < minDist) {
				minDist = intersectionResult.distAlongRay;
				closestIntersection.point = intersectionResult.point;
				closestIntersection.mesh = &obj;
				closestIntersection.triangle = &obj.triangles[trIdx];
			}
		}
	}

	if (minDist == -1.f) {
		return scene.backgroundColor;
	}

	return shadeIntersection(closestIntersection);
}

Color RayTracer::shadeIntersection(const TriangleIntersection &intersection) const {
	Color result = { 0.f, 0.f, 0.f };
	// Calculate intersected triangle's normal
	const Vec3f trNormal = getTriangleNormal(
		intersection.mesh->vertices[intersection.triangle->x],
		intersection.mesh->vertices[intersection.triangle->y],
		intersection.mesh->vertices[intersection.triangle->z]
	);
	// Traverse lights in the scene
	for (int lIdx = 0; lIdx < scene.lightsCount; lIdx++) {
		const Light &light = scene.lights[lIdx];
		// Calculate vector from the intersection point to the light
		const Vec3f lightVec = light.position - intersection.point;
		// Calculate light unit direction
		const Vec3f lightDir = lightVec.getNormal();
		// Create a shadow ray in the light direction
		const Ray shadowRay = {
			// with its origin at the intersection point,
			// but offset with some tiny amount (shadow bias) along the triangle's normal
			intersection.point + trNormal * scene.shadowBias,
			lightDir
		};
		// Check if the intersection point is in shadow.
		// It's in shadow if the shadow ray intersects any triangles in the scene.
		bool inShadow = false;
		// Traverse all objects in the scene
		for (int objIdx = 0; objIdx < scene.objectsCount; objIdx++) {
			const Mesh &obj = scene.objects[objIdx];
			// Traverse all triangles of the object
			for (int trIdx = 0; trIdx < obj.trianglesCount; trIdx++) {
				// Check for intersection between the shadow ray and the current triangle.
				const RayTriangleIntersectionResult intersectionResult = rayTriangleIntersection(
					shadowRay,
					obj.vertices[obj.triangles[trIdx].x],
					obj.vertices[obj.triangles[trIdx].y],
					obj.vertices[obj.triangles[trIdx].z]
				);
				// If there is an intersection,
				// then the point is in shadow and we can stop looking for other intersections.
				// Here we are considering both intersections from the front and from the back side of the triangle.
				if (intersectionResult.doesIntersect) {
					inShadow = true;
					break;
				}
			}
			if (inShadow) {
				break;
			}
		}
		// If the point is not in shadow, then the current light contributes to the final result
		if (!inShadow) {
			// Calculate the radius and area of the sphere centered at the light and passing through the intersection point
			const float sphRadius = lightVec.getLength();
			const float sphArea = 4 * M_PI * sphRadius * sphRadius;
			// Calculate the cosine law for the light direction and triangle's normal
			const float cosLaw = getMax(0.f, dotProduct(lightDir, trNormal));
			result += light.albedo * ((light.intensity / sphArea) * cosLaw);
		}
	}
	
	return result;
}

bool RayTracer::writePixelsToFile(const char *filepath) const {
	if (!pixels) {
		return false;
	}

	// Open stream to the output file
	std::ofstream ppmFileStream(filepath, std::ios::out | std::ios::binary);
	if (!ppmFileStream.is_open()) {
		return false;
	}
	// Write PPM metadata about PPM version, image resolution and max color component
    ppmFileStream << "P3\n";
    ppmFileStream << scene.imageResolution.x << " " << scene.imageResolution.y << "\n";
    ppmFileStream << maxColorComponent << "\n";

    // Traverse pixels of the image
    for (Vec2i pixel = { 0, 0 }; pixel.y < scene.imageResolution.y; pixel.y++) {
		for (pixel.x = 0; pixel.x < scene.imageResolution.x; pixel.x++) {
			// Index of the pixel in the pixels array
			const int pixIdx = pixel.y * scene.imageResolution.x + pixel.x;
			// Use the pixel's color from the pixels array
			const Color color = pixels[pixIdx];
			// Write the color to the output image file for the current pixel
			ppmFileStream << int(color.x * maxColorComponent)
				<< " " << int(color.y * maxColorComponent)
				<< " " << int(color.z * maxColorComponent)
				<< "\t";
		}
		ppmFileStream << "\n";
	}

    ppmFileStream.close();

	return true;
}