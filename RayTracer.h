#pragma once

#include "Camera.h"
#include "Scene.h"
#include "utils/MathUtils.h"

using namespace MathUtils;

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

private: /* functions */
	/// Generates rays for all pixels of the image.
	/// Saves them to the member array of rays.
	void generateRays() const;
	
	/// Generates a single ray for a single pixel of the image.
	/// @param[in] pixel Index of a pixel from the image
	/// @return Generated ray through the given pixel
	Ray generateRay(const Vec2i &pixel) const;

	/// Traces all generated rays for all pixels of the image.
	/// Saves the results to the pixels member array.
	void traceRays() const;

	/// Traces a single ray.
	/// Finds where the ray intersects the scene and what color should that ray be.
	/// @param[in] ray The ray to be traced
	/// @return Calculated color for the ray
	Color traceRay(const Ray &ray) const;

	/// Shades a point of intersection on a triangle's surface.
	/// Returns the shaded color.
	/// @param[in] intersection Intersection of a camera ray with a triangle
	/// @return Shaded color
	Color shadeIntersection(const TriangleIntersection &intersection) const;

	/// Writes the pixels of the ray tracer to a PPM image file
	/// @param[in] filepath Path to the output PPM image file
	/// @return True on success
	bool writePixelsToFile(const char *filepath) const;

private: /* variables */
	/// The scene to be rendered
	Scene scene;

	/// Array of generated rays
	mutable Ray *rays = nullptr;
	/// Array of results of traced rays
	mutable Color *pixels = nullptr;
};