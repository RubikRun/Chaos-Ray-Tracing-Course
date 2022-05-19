#include "Camera.h"

#include <cmath>
#include "utils/JsonUtils.h"

void Camera::readFromJson(const rapidjson::Value &json) {
	if (!json.IsNull()) {
		assert(json.IsObject());

		const rapidjson::Value &matrixVal = json.FindMember("matrix")->value;
		if (!matrixVal.IsNull()) {
			assert(matrixVal.IsArray());
			rotation = JsonUtils::getMatrix3fFromJsonArr(matrixVal.GetArray());
		}

		const rapidjson::Value &positionVal = json.FindMember("position")->value;
		if (!positionVal.IsNull()) {
			assert(positionVal.IsArray());
			position = JsonUtils::getVec3fFromJsonArr(positionVal.GetArray());
		}
	}
}

void Camera::dolly(float amount) {
	position += rotation * Vec3f(0.f, 0.f, -amount);
}

void Camera::boom(float amount) {
	position += rotation * Vec3f(0.f, amount, 0.f);
}

void Camera::truck(float amount) {
	position += rotation * Vec3f(amount, 0.f, 0.f);
}

void Camera::tilt(float angle) {
	rotation = rotation * Matrix3f(
		{ 1.f, 0.f, 0.f},
		{ 0.f, cosf(angle), sinf(angle) },
		{ 0.f, -sinf(angle), cosf(angle) }
	);
}

void Camera::pan(float angle) {
	rotation = rotation * Matrix3f(
		{ cosf(angle), 0.f, sinf(angle) },
		{ 0.f, 1.f, 0.f },
		{ -sinf(angle), 0.f, cosf(angle) }
	);
}

void Camera::roll(float angle) {
	rotation = rotation * Matrix3f(
		{ cosf(angle), sinf(angle), 0.f },
		{ -sinf(angle), cosf(angle), 0.f },
		{ 0.f, 0.f, 1.f}
	);
}