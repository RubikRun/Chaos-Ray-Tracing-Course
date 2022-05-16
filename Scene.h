#pragma once

#include "utils.hpp"
#include "Camera.h"
#include "Mesh.h"

#include <string>

/// Class representing the scene,
/// holding data about all objects, camera and settings
struct Scene {
	/// Reads the scene from a file
	void readFromFile(const std::string &filepath);

	/// Array of mesh objects in the scene
	Mesh *objects = nullptr;
	int objectsCount = 0;

	/// Camera through which the scene will be rendered
	Camera camera;

	/// Resolution of the output image
	Vec2i imageResolution;

	/// Color of the background
	Color backgroundColor = Color(0, 0, 0);
};