#include "Scene.h"

#include "utils/JsonUtils.h"

static void readSceneSettingsFromJson(Scene &scene, const rapidjson::Value &json) {
	if (!json.IsNull()) {
		assert(json.IsObject());

		const rapidjson::Value &bgColorVal = json.FindMember("background_color")->value;
		if (!bgColorVal.IsNull()) {
			assert(bgColorVal.IsArray());
			scene.backgroundColor = JsonUtils::getColorFromJsonArr(bgColorVal.GetArray());
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

		rapidjson::Value::ConstMemberIterator shadowBiasIt = json.FindMember("shadow_bias");
		if (shadowBiasIt != json.MemberEnd()) {
			const rapidjson::Value &shadowBiasVal = shadowBiasIt->value;
			assert(shadowBiasVal.IsNumber());
			scene.shadowBias = shadowBiasVal.GetFloat();
		}
	}
}

void Scene::readFromJson(const rapidjson::Value &json) {
	const rapidjson::Value &settingsVal = json.FindMember("settings")->value;
	readSceneSettingsFromJson(*this, settingsVal);

	const rapidjson::Value &cameraVal = json.FindMember("camera")->value;
	camera.readFromJson(cameraVal);

	const rapidjson::Value &objectsVal = json.FindMember("objects")->value;
	if (!objectsVal.IsNull()) {
		assert(objectsVal.IsArray());

		objectsCount = objectsVal.Size();
		objects = new Mesh[objectsCount];

		for (int i = 0; i < objectsCount; i++) {
			objects[i].readFromJson(objectsVal[i]);
		}
	}

	const rapidjson::Value &lightsVal = json.FindMember("lights")->value;
	if (!lightsVal.IsNull()) {
		assert(lightsVal.IsArray());

		lightsCount = lightsVal.Size();
		lights = new Light[lightsCount];

		for (int i = 0; i < lightsCount; i++) {
			lights[i].readFromJson(lightsVal[i]);
		}
	}
}