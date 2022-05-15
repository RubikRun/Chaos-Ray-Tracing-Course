#pragma once

#include "utils.hpp"

/// Class holding data about the camera
struct Camera {
	/// Creates a camera with default parameters
	Camera(){}

	/// Creates a camera with given view parameters
	/// @param[in] viewSize Size of the image in world space
	/// @param[in] viewDepth Distance between camera and image plane 
	Camera(const Vec2f &viewSize, float viewDepth)
		: viewSize(viewSize)
		, viewDepth(viewDepth)
	{}

	/// Creates a camera with given view parameters, position and rotation
	/// @param[in] viewSize Size of the image in world space
	/// @param[in] viewDepth Distance between camera and image plane
	/// @param[in] position Position of the camera in world space
	/// @param[in] rotation Rotation matrix by which the camera will be rotated
	Camera(const Vec2f &viewSize, float viewDepth, const Vec3f &position, const Matrix3f &rotation)
		: viewSize(viewSize)
		, viewDepth(viewDepth)
		, position(position)
		, rotation(rotation)
	{}

	/// Size of the image in world space
	Vec2f viewSize = { 2.f, 2.f };
	/// Distance between camera and image plane
	float viewDepth = 1.f;
	/// Position of the camera in world space
	Vec3f position = { 0.f, 0.f, 0.f };
	/// Rotation matrix by which the camera will be rotated
	Matrix3f rotation = {
		{ 1.f, 0.f, 0.f },
		{ 0.f, 1.f, 0.f },
		{ 0.f, 0.f, 1.f }
	};

	/// Moves the camera forward/backwards by some amount according to its rotation
	void dolly(float amount);
	/// Moves the camera up/down by some amount according to its rotation
	void boom(float amount);
	/// Moves the camera left/right by some amount according to its rotation
	void truck(float amount);
	/// Rotates the camera up/down (around its X axis) by some angle
	void tilt(float angle);
	/// Rotates the camera left/right (around its Y axis) by some angle
	void pan(float angle);
	/// Rotates the camera clockwise/counter-clockwise (around its Z axis) by some angle
	void roll(float angle);
};