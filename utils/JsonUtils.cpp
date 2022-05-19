#include "JsonUtils.h"

#include "rapidjson/istreamwrapper.h"
#include <fstream>
#include <iostream>

namespace JsonUtils {

rapidjson::Document readJsonDocument(const std::string &filepath) {
    // Open the file
	std::ifstream ifs(filepath);
	assert(ifs.is_open());
    // Create a JSON stream to the opened file
	rapidjson::IStreamWrapper isw(ifs);
    // Create a JSON document by parsing the stream
	rapidjson::Document doc;
	doc.ParseStream(isw);
    // Check for error
	if (doc.HasParseError()) {
		std::cout << "Error: " << doc.GetParseError() << "\n";
		std::cout << "Offset: " << doc.GetErrorOffset() << "\n";
		assert(false);
	}
	assert(doc.IsObject());
    // Return the JSON document
	return doc;
}

Vec3f getVec3fFromJsonArr(const rapidjson::Value::ConstArray &arr) {
	assert(arr.Size() == 3);
	assert(arr[0].IsNumber() && arr[1].IsNumber() && arr[2].IsNumber());
	return Vec3f(arr[0].GetFloat(), arr[1].GetFloat(), arr[2].GetFloat());
}

Vec3i getVec3iFromJsonArr(const rapidjson::Value::ConstArray &arr) {
	assert(arr.Size() == 3);
	assert(arr[0].IsInt() && arr[1].IsInt() && arr[2].IsInt());
	return Vec3i(arr[0].GetInt(), arr[1].GetInt(), arr[2].GetInt());
}

Color getColorFromJsonArr(const rapidjson::Value::ConstArray &arr) {
	assert(arr.Size() == 3);
	assert(arr[0].IsNumber() && arr[1].IsNumber() && arr[2].IsNumber());
	return Color(arr[0].GetFloat(), arr[1].GetFloat(), arr[2].GetFloat());
}

Matrix3f getMatrix3fFromJsonArr(const rapidjson::Value::ConstArray &arr) {
	assert(arr.Size() == 9);
	assert(
		arr[0].IsNumber() && arr[1].IsNumber() && arr[2].IsNumber() &&
		arr[3].IsNumber() && arr[4].IsNumber() && arr[5].IsNumber() &&
		arr[6].IsNumber() && arr[7].IsNumber() && arr[8].IsNumber()
	);
	return Matrix3f(
		{ arr[0].GetFloat(), arr[1].GetFloat(), arr[2].GetFloat() },
		{ arr[3].GetFloat(), arr[4].GetFloat(), arr[5].GetFloat() },
		{ arr[6].GetFloat(), arr[7].GetFloat(), arr[8].GetFloat() }
	);
}

} // namespace JsonUtils