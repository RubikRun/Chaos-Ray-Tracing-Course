#include "RayTracer.h"
#include "Scene.h"

#include "utils/JsonUtils.h"

int main() {
	Scene scene;
	rapidjson::Document jsonDoc = JsonUtils::readJsonDocument("scenes/scene1.crtscene");
	scene.readFromJson(jsonDoc);

	RayTracer rayTracer(scene);
	rayTracer.renderImage("render/01.ppm");

	return 0;
}