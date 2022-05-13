#pragma once

#include "utils.hpp"

/// Class holding data about the 2D image in world space.
struct Image {
	/// Resolution of the output image, number of pixels horizontally and vertically
	Vec2i resolution;
	/// Size of the image in world space.
	/// The image is considered to be in the XY plane with Z = -distToCamera
	/// with its center at (0, 0, -distToCamera)
	Vec2f size;
	/// Distance from the camera to the image in world space.
	float distToCamera;

	int getPixelCount() const {
		return resolution.x * resolution.y;
	}
};

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

/// Scene of triangles in world space
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
	/// Creates a ray tracer for the given image and scene.
	/// @param[in] imageRect Image whose pixels will be used to generate rays
	/// @param[in] scene Scene to be rendered
	RayTracer(const Image &image, const Scene &scene);

	/// Frees all memory
	~RayTracer();

	/// Writes an output image based on the traced rays.
	/// @param[in] filepath Path to the output image
	/// @return True on success
	bool writeImage(const char *filepath) const;

private: /*functions */
	/// Generates rays for all pixels of the image.
	/// Saves them to the member array of rays.
	void generateRays();
	
	/// Generates a single ray for a single pixel of the image.
	/// @param[in] pixel Index of a pixel from the image
	/// @return Generated ray through the given pixel
	Ray generateRay(const Vec2i &pixel) const;

	/// Traces all generated rays for all pixels of the image.
	/// Saves the results to the member array of ray results.
	void traceRays();

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
	/// The image used to generate rays
	Image image;

	/// The scene to be rendered
	Scene scene;

	/// Array of generated rays
	Ray *rays = nullptr;
	/// Array of results of traced rays
	RayResult *rayResults = nullptr;
};