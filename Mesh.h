#pragma once

#include "utils/MathUtils.h"
#include "rapidjson/document.h"

using namespace MathUtils;

/// Class representing a single mesh object
///	made up of vertices connected into triangles.
struct Mesh {
	/// Creates an empty mesh
	Mesh(){}

	/// Creates a mesh with some vertices and triangles
	Mesh(Vec3f *vertices, int verticesCount, Vec3i *triangles, int trianglesCount);

	/// Reads the mesh from a JSON value
	void readFromJson(const rapidjson::Value &json);

	/// Array of vertices represented with their 3 coordinates
	Vec3f *vertices = nullptr;
	int verticesCount = 0;

	/// Array of triangles represented with the indices of their 3 vertices
	Vec3i *triangles = nullptr;
	int trianglesCount = 0;
};

/// Class representing an intersection of a triangle
struct TriangleIntersection {
	/// The point of intersection in world space
	Vec3f point = { -1.f, -1.f, -1.f };
	/// Pointer to the mesh that is intersected
	const Mesh *mesh = nullptr;
	/// Pointer to the triangle that is intersected
	const Vec3i *triangle = nullptr;
};