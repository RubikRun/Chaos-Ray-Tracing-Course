#include "Light.h"

#include "utils/JsonUtils.h"

void Light::readFromJson(const rapidjson::Value &json) {
	const rapidjson::Value &positionVal = json.FindMember("position")->value;
	if (!positionVal.IsNull()) {
		assert(positionVal.IsArray());
		position = JsonUtils::getVec3fFromJsonArr(positionVal.GetArray());
	}

	const rapidjson::Value &intensityVal = json.FindMember("intensity")->value;
	if (!intensityVal.IsNull()) {
		assert(intensityVal.IsNumber());
		intensity = intensityVal.GetFloat();
	}

	rapidjson::Value::ConstMemberIterator albedoIt = json.FindMember("albedo");
	if (albedoIt != json.MemberEnd()) {
		const rapidjson::Value &albedoVal = albedoIt->value;
		if (!albedoVal.IsNull()) {
			assert(albedoVal.IsArray());
			albedo = JsonUtils::getColorFromJsonArr(albedoVal.GetArray());
		}
	}
}