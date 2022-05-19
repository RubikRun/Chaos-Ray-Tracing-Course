#pragma once

#include "utils/MathUtils.h"
#include "rapidjson/document.h"

using namespace MathUtils;

/// Class representing a light in the scene
struct Light {
	/// Creates a default light
	Light(){}

	/// Creates a light with some position and intensity
	Light(const Vec3f &position, float intensity)
		: position(position), intensity(intensity)
	{}

	/// Creates a light with position, intensity and albedo
	Light(const Vec3f &position, float intensity, const Color &albedo)
		: position(position), intensity(intensity), albedo(albedo)
	{}

	/// Reads the light from a JSON value
	void readFromJson(const rapidjson::Value &json);

	/// Position of the light
	Vec3f position = { 0.f, 10.f, 0.f };

	/// Intensity of the light
	float intensity = 1000.f;

	/// Albedo/color of the light
	Color albedo = { 0.9f, 0.9f, 0.9f };
};