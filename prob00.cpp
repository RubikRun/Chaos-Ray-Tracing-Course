#include "RayTracer.h"
#include "Scene.h"

#include "utils/JsonUtils.h"

int main() {
	Scene scene;
	rapidjson::Document jsonDoc = JsonUtils::readJsonDocument("scenes/scene0.crtscene");
	scene.readFromJson(jsonDoc);

	RayTracer rayTracer(scene);
	rayTracer.renderImage("render/00.ppm");

	return 0;
}