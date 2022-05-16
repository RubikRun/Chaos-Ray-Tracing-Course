#include "RayTracer.h"

#include <fstream>

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
	rayResults = new RayResult[totalPixels];
	traceRays();

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
			// Index of the ray in the array that corresponds to this pixel
			const int rayIdx = pixel.y * scene.imageResolution.x + pixel.x;
			// Use the ray's color to color the pixel
			const Color color = rayResults[rayIdx].color;
			// Write the color to the output image file for the current pixel
			ppmFileStream << int(color.r * maxColorComponent)
				<< " " << int(color.g * maxColorComponent)
				<< " " << int(color.b * maxColorComponent)
				<< "\t";
		}
		ppmFileStream << "\n";
	}

    ppmFileStream.close();

    return true;
}

void RayTracer::generateRays() const {
	// Traverse pixels of the image
	for (Vec2i pixel = { 0, 0 }; pixel.y < scene.imageResolution.y; pixel.y++) {
		for (pixel.x = 0; pixel.x < scene.imageResolution.x; pixel.x++) {
			// Index of the ray in the array that corresponds to this pixel
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

	ray.orig = scene.camera.position;
	ray.dir = scene.camera.rotation * cameraToPixel.getNormal();
	ray.pixel = pixel;

	return ray;
}

void RayTracer::traceRays() const {
	// Traverse rays
	for (int rayIdx = 0; rayIdx < scene.imageResolution.x * scene.imageResolution.y; rayIdx++) {
		// Trace each ray and save the result
		rayResults[rayIdx] = traceRay(rays[rayIdx]);
	}
}

RayResult RayTracer::traceRay(const Ray &ray) const {
	// This will be the closest ray result across all triangles
	RayResult closestRayResult;
	closestRayResult.tDist = -1.f;
	// Traverse all objects in the scene
	for (int objIdx = 0; objIdx < scene.objectsCount; objIdx++) {
		const Mesh &currObj = scene.objects[objIdx];
		// Traverse all triangles of the object
		for (int trIdx = 0; trIdx < currObj.trianglesCount; trIdx++) {
			// Trace the ray to the current triangle
			const RayResult currRayResult = intersectTriangle(
				currObj.vertices[currObj.triangles[trIdx].x],
				currObj.vertices[currObj.triangles[trIdx].y],
				currObj.vertices[currObj.triangles[trIdx].z],
				ray
			);
			if (currRayResult.tDist == -1.f) {
				continue;
			}
			// If the current ray intersection is closer than the closest intersection so far, use the current
			if (currRayResult.tDist < closestRayResult.tDist || closestRayResult.tDist == -1.f) {
				closestRayResult = currRayResult;
			}
		}
	}
	
	return closestRayResult;
}

RayResult RayTracer::intersectTriangle(const Vec3f &aVert, const Vec3f &bVert, const Vec3f &cVert,const Ray &ray) const {
	// Normal of the triangle
	const Vec3f trNorm = getTriangleNormal(
		aVert,
		bVert,
		cVert
	);
	// Length of the ray projected on the triangle's normal.
	// Taken with a minus so that it points towards the triangle
	const float rayProj = -dotProduct(ray.dir, trNorm);
	// Distance from the camera to the triangle's plane
	const float distToTrPlane = -dotProduct(aVert - scene.camera.position, trNorm);

	// If the ray projection on the triangle's normal is approximately zero,
	// than the ray is almost perpendicular to the triangle's plane,
	// so we don't bother to intersect it with the triangle
	if (isApproxZero(rayProj)) {
		return RayResult();
	}
	// If this distance from the camera to the triangle's plane is negative,
	// this means that the ray is looking at the back side of the triangle,
	// so we ignore it
	if (distToTrPlane < 0.f) {
		return RayResult();
	}

	// Distance/time along the ray from the ray origin to the point of intersection
	const float tDist = distToTrPlane / rayProj;
	// Point of intersection between the ray and the triangle's plane
	const Vec3f interPoint = ray.orig + ray.dir * tDist;

	// Check if the point of intersection is inside the triangle
	const bool insideTriangle = (
		dotProduct(
			trNorm,
			crossProduct(bVert - aVert, interPoint - aVert)
		) > 0.f
		&&
		dotProduct(
			trNorm,
			crossProduct(cVert - bVert, interPoint - bVert)
		) > 0.f
		&&
		dotProduct(
			trNorm,
			crossProduct(aVert - cVert, interPoint - cVert)
		) > 0.f
	);

	if (!insideTriangle) {
		return RayResult();
	}
	
	return RayResult(
		{ maxColorComponent, maxColorComponent, maxColorComponent },
		tDist
	);
}