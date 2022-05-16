#pragma once

#include "Camera.h"
#include "Scene.h"
#include "utils.hpp"

/// Class representing a ray traced by the ray tracer.
struct Ray {
	/// Origin of the ray, a point in world space
	Vec3f orig;
	/// Direction of the ray, a normal vector
	Vec3f dir;
	/// Index of the pixel through which the ray is passing
	Vec2i pixel;
};

/// Result of a traced ray
struct RayResult {
	RayResult(){}

	RayResult(const Color &color, float tDist)
		: color(color), tDist(tDist)
	{}

	/// Color of the ray
	Color color = { 0, 0, 0 };
	/// Time/Distance from the origin of the ray to the point of intersection
	float tDist = -1.f;
};

/// Class representing the ray tracer,
/// capable of generating and tracing rays based on the pixels of some image,
/// and using them to generate an output image file.
struct RayTracer {
	/// Creates a ray tracer for a given scene
	/// @param[in] scene Scene to be rendered by the ray tracer
	RayTracer(const Scene &scene);

	/// Frees all memory
	~RayTracer();

	/// Renders an image and writes it to an image file.
	/// @param[in] filepath Path to the output image
	/// @return True on success
	bool renderImage(const char *filepath) const;

private: /*functions */
	/// Generates rays for all pixels of the image.
	/// Saves them to the member array of rays.
	void generateRays() const;
	
	/// Generates a single ray for a single pixel of the image.
	/// @param[in] pixel Index of a pixel from the image
	/// @return Generated ray through the given pixel
	Ray generateRay(const Vec2i &pixel) const;

	/// Traces all generated rays for all pixels of the image.
	/// Saves the results to the member array of ray results.
	void traceRays() const;

	/// Traces a single ray for a single pixel of the image.
	/// Finds where the ray intersects the scene and what color should that ray be.
	/// @param[in] ray The ray to be traced
	/// @return Calculated ray result
	RayResult traceRay(const Ray &ray) const;

	/// Intersects a single triangle with a ray
	/// @param[in] aVert, bVert, cVert The vertices of the triangle to be intersected
	/// @param[in] ray The ray to intersect with
	/// @return The result of the ray intersection
	RayResult intersectTriangle(
		const Vec3f &aVert,
		const Vec3f &bVert,
		const Vec3f &cVert,
		const Ray &ray
	) const;

private: /* variables */
	/// The scene to be rendered
	Scene scene;

	/// Array of generated rays
	mutable Ray *rays = nullptr;
	/// Array of results of traced rays
	mutable RayResult *rayResults = nullptr;
};