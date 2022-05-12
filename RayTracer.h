#pragma once

#include "utils.hpp"

/// Class holding data about the image.
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
	/// Color of the ray
	Color color;
};

/// Class representing the ray tracer,
/// capable of generating and tracing rays based on some image,
/// and using them to generate the output image file.
struct RayTracer {
	/// Creates a ray tracer for the given image.
	/// @param[in] imageRect Image whose pixels will be used to generate rays
	RayTracer(const Image &image);

	/// Frees all memory
	~RayTracer();

	/// Writes the generated and traced rays to an output image
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

private: /* variables */
	/// The image used to generate rays
	Image image;

	/// Array of generated and/or traced rays
	Ray *rays = nullptr;
};