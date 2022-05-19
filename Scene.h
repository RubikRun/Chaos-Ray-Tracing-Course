#pragma once

#include "utils/MathUtils.h"
#include "Camera.h"
#include "Mesh.h"
#include "Light.h"

#include "rapidjson/document.h"

using namespace MathUtils;

/// Class representing the scene,
/// holding data about all objects, camera and settings
struct Scene {
	/// Reads the scene from a JSON value
	void readFromJson(const rapidjson::Value &json);

	/// Array of mesh objects in the scene
	Mesh *objects = nullptr;
	int objectsCount = 0;

	/// Array of lights in the scene
	Light *lights = nullptr;
	int lightsCount = 0;

	/// Camera through which the scene will be rendered
	Camera camera;

	/// Resolution of the output image
	Vec2i imageResolution;

	/// Color of the background
	Color backgroundColor = Color(0, 0, 0);

	/// Bias used to offset the origin of a shadow ray in the direction of the surface normal,
	/// so that the shadow ray doesn't accidentally intersect the surface where it comes from,
	/// due to floaing point precision
	float shadowBias = 0.00001f;
};