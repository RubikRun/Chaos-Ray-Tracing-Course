#pragma once

#include "MathUtils.h"

#include "rapidjson/document.h"

using namespace MathUtils;

namespace JsonUtils {

/// Reads a JSON document from a file
rapidjson::Document readJsonDocument(const std::string &filepath);

/// Extracts a Vector of 3 floats from a JSON array
Vec3f getVec3fFromJsonArr(const rapidjson::Value::ConstArray &arr);

/// Extracts a Vector of 3 ints from a JSON array
Vec3i getVec3iFromJsonArr(const rapidjson::Value::ConstArray &arr);

/// Extracts a color from a JSON array
Color getColorFromJsonArr(const rapidjson::Value::ConstArray &arr);

/// Extracts a 3 by 3 matrix from a JSON array
Matrix3f getMatrix3fFromJsonArr(const rapidjson::Value::ConstArray &arr);

} // namespace JsonUtils