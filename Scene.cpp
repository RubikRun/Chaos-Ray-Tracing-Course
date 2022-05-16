#include "Scene.h"
#include "rapidjson/document.h"
#include "rapidjson/istreamwrapper.h"
#include <iostream>
#include <fstream>

static rapidjson::Document getJsonDocument(const std::string &filepath) {
	std::ifstream ifs(filepath);
	assert(ifs.is_open());

	rapidjson::IStreamWrapper isw(ifs);
	rapidjson::Document doc;
	doc.ParseStream(isw);

	if (doc.HasParseError()) {
		std::cout << "Error: " << doc.GetParseError() << "\n";
		std::cout << "Offset: " << doc.GetErrorOffset() << "\n";
		assert(false);
	}

	assert(doc.IsObject());
	return doc;
}

static Vec3f getVec3fFromJsonArr(const rapidjson::Value::ConstArray &arr) {
	assert(arr.Size() == 3);
	assert(arr[0].IsNumber() && arr[1].IsNumber() && arr[2].IsNumber());
	return Vec3f(
		arr[0].GetFloat(),
		arr[1].GetFloat(),
		arr[2].GetFloat()
	);
}

static Vec3i getVec3iFromJsonArr(const rapidjson::Value::ConstArray &arr) {
	assert(arr.Size() == 3);
	assert(arr[0].IsInt() && arr[1].IsInt() && arr[2].IsInt());
	return Vec3i(
		arr[0].GetInt(),
		arr[1].GetInt(),
		arr[2].GetInt()
	);
}

static Color getColorFromJsonArr(const rapidjson::Value::ConstArray &arr) {
	assert(arr.Size() == 3);
	assert(arr[0].IsNumber() && arr[1].IsNumber() && arr[2].IsNumber());
	return Color(
		arr[0].GetFloat(),
		arr[1].GetFloat(),
		arr[2].GetFloat()
	);
}

static Matrix3f getMatrix3fFromJsonArr(const rapidjson::Value::ConstArray &arr) {
	assert(arr.Size() == 9);
	assert(
		arr[0].IsNumber() && arr[1].IsNumber() && arr[2].IsNumber()
		&& arr[3].IsNumber() && arr[4].IsNumber() && arr[5].IsNumber()
		&& arr[6].IsNumber() && arr[7].IsNumber() && arr[8].IsNumber()
	);
	return Matrix3f(
		{ arr[0].GetFloat(), arr[1].GetFloat(), arr[2].GetFloat() },
		{ arr[3].GetFloat(), arr[4].GetFloat(), arr[5].GetFloat() },
		{ arr[6].GetFloat(), arr[7].GetFloat(), arr[8].GetFloat() }
	);
}

static void readSceneSettingsFromJson(Scene &scene, const rapidjson::Value &json) {
	if (!json.IsNull()) {
		assert(json.IsObject());

		const rapidjson::Value &bgColorVal = json.FindMember("background_color")->value;
		if (!bgColorVal.IsNull()) {
			assert(bgColorVal.IsArray());
			scene.backgroundColor = getColorFromJsonArr(bgColorVal.GetArray());
		}

		const rapidjson::Value &imageSettingsVal = json.FindMember("image_settings")->value;
		if (!imageSettingsVal.IsNull()) {
			assert(imageSettingsVal.IsObject());
			const rapidjson::Value &imageWidthVal = imageSettingsVal.FindMember("width")->value;
			const rapidjson::Value &imageHeightVal = imageSettingsVal.FindMember("height")->value;
			assert(!imageWidthVal.IsNull() && imageWidthVal.IsInt() && !imageHeightVal.IsNull() && imageHeightVal.IsInt());
			scene.imageResolution.x = imageWidthVal.GetInt();
			scene.imageResolution.y = imageHeightVal.GetInt();
		}
	}
}

static void readCameraFromJson(Camera &camera, const rapidjson::Value &json) {
	if (!json.IsNull()) {
		assert(json.IsObject());

		const rapidjson::Value &matrixVal = json.FindMember("matrix")->value;
		if (!matrixVal.IsNull()) {
			assert(matrixVal.IsArray());
			camera.rotation = getMatrix3fFromJsonArr(matrixVal.GetArray());
		}

		const rapidjson::Value &positionVal = json.FindMember("position")->value;
		if (!positionVal.IsNull()) {
			assert(positionVal.IsArray());
			camera.position = getVec3fFromJsonArr(positionVal.GetArray());
		}
	}
}

void Scene::readFromFile(const std::string &filepath) {
	rapidjson::Document doc = getJsonDocument(filepath);

	const rapidjson::Value &settingsVal = doc.FindMember("settings")->value;
	readSceneSettingsFromJson(*this, settingsVal);

	const rapidjson::Value &cameraVal = doc.FindMember("camera")->value;
	readCameraFromJson(camera, cameraVal);

	const rapidjson::Value &objectsVal = doc.FindMember("objects")->value;
	if (!objectsVal.IsNull()) {
		assert(objectsVal.IsArray());

		objectsCount = objectsVal.Size();
		objects = new Mesh[objectsCount];

		for (int i = 0; i < objectsCount; i++) {
			objects[i].readFromJson(objectsVal[i]);
		}
	}
}