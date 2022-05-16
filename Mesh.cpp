#include "Mesh.h"

Mesh::Mesh(Vec3f *vertices, int verticesCount, Vec3i *triangles, int trianglesCount)
	: vertices(vertices)
	, verticesCount(verticesCount)
	, triangles(triangles)
	, trianglesCount(trianglesCount)
{}

static void readVerticesFromJsonArr(Vec3f* &vertices, int &verticesCount, const rapidjson::Value::ConstArray &arr) {
	assert(arr.Size() % 3 == 0);
	verticesCount = arr.Size() / 3;

	if (verticesCount <= 0) {
		vertices = nullptr;
		return;
	}

	vertices = new Vec3f[verticesCount];
	for (int vIdx = 0; vIdx < verticesCount; vIdx++) {
		assert(
			arr[vIdx * 3 + 0].IsNumber()
			&& arr[vIdx * 3 + 1].IsNumber()
			&& arr[vIdx * 3 + 2].IsNumber()
		);
		vertices[vIdx] = {
			arr[vIdx * 3 + 0].GetFloat(),
			arr[vIdx * 3 + 1].GetFloat(),
			arr[vIdx * 3 + 2].GetFloat()
		};
	}
}

static void readTrianglesFromJsonArr(Vec3i* &triangles, int &trianglesCount, const rapidjson::Value::ConstArray &arr) {
	assert(arr.Size() % 3 == 0);
	trianglesCount = arr.Size() / 3;

	if (trianglesCount <= 0) {
		triangles = nullptr;
		return;
	}

	triangles = new Vec3i[trianglesCount];
	for (int trIdx = 0; trIdx < trianglesCount; trIdx++) {
		assert(
			arr[trIdx * 3 + 0].IsInt()
			&& arr[trIdx * 3 + 1].IsInt()
			&& arr[trIdx * 3 + 2].IsInt()
		);
		triangles[trIdx] = {
			arr[trIdx * 3 + 0].GetInt(),
			arr[trIdx * 3 + 1].GetInt(),
			arr[trIdx * 3 + 2].GetInt()
		};
	}
}

void Mesh::readFromJson(const rapidjson::Value &json) {
	if (vertices) {
		delete[] vertices;
	}
	verticesCount = 0;
	if (triangles) {
		delete[] triangles;
	}
	trianglesCount = 0;

	const rapidjson::Value &verticesVal = json.FindMember("vertices")->value;
	if (!verticesVal.IsNull()) {
		assert(verticesVal.IsArray());
		readVerticesFromJsonArr(vertices, verticesCount, verticesVal.GetArray());
	}

	const rapidjson::Value &trianglesVal = json.FindMember("triangles")->value;
	if (!trianglesVal.IsNull()) {
		assert(trianglesVal.IsArray());
		readTrianglesFromJsonArr(triangles, trianglesCount, trianglesVal.GetArray());
	}
}