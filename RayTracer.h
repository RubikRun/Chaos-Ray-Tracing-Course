#pragma once

#include "Camera.h"
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

/// Class representing the scene consisting of triangles
struct Scene {
	Scene(){}

	Scene(Triangle *triangles, int trianglesCount)
		: triangles(triangles), trianglesCount(trianglesCount)
	{}

	/// Array of triangles in the scene
	Triangle *triangles = nullptr;
	/// Number of triangles
	int trianglesCount = 0;
};

/// Class representing the ray tracer,
/// capable of generating and tracing rays based on the pixels of some image,
/// and using them to generate an output image file.
struct RayTracer {
	/// Creates a ray tracer with a given camera and image resolution
	/// @param[in] camera Camera used to generate rays
	/// @param[in] imageResolution Resolution of the output image
	RayTracer(const Camera &camera, const Vec2i &imageResolution);

	/// Frees all memory
	~RayTracer();

	/// Sets the scene to be rendered
	void setScene(const Scene &scene);

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
	/// @param[in] triangle The triangle to be intersected
	/// @param[in] ray The ray to intersect with
	/// @return The result of the ray intersection
	RayResult intersectTriangle(const Triangle &triangle, const Ray &ray) const;

private: /* variables */
	/// Camera used to generate rays
	Camera camera;
	/// The scene to be rendered
	Scene scene;
	/// Resolution of the output image
	Vec2i imageResolution;

	/// Array of generated rays
	mutable Ray *rays = nullptr;
	/// Array of results of traced rays
	mutable RayResult *rayResults = nullptr;
};