#include "utils.hpp"

#include <iostream>

int main() {
	const Triangle tr1 = Triangle({
		{ -1.75f, -1.75f, -3.f },
		{ 1.75f, -1.75f, -3.f },
		{ 0.f, 1.75f, -3.f }
	});
	const Vec3f tr1Normal = tr1.getNormalVector();
	const float tr1Area = tr1.getArea();
	std::cout << "Triangle with vertices (-1.75, -1.75, -3), (1.75, -1.75, -3) and (0, 1.75, -3) has normal vector ("
		<< tr1Normal.x << ", " << tr1Normal.y << ", " << tr1Normal.z << ") and area = "
		<< tr1Area << "\n";

	const Triangle tr2 = Triangle({
		{ 0.f, 0.f, -1.f },
		{ 1.f, 0.f, 1.f },
		{ -1.f, 0.f, 1.f }
	});
	const Vec3f tr2Normal = tr2.getNormalVector();
	const float tr2Area = tr2.getArea();
	std::cout << "Triangle with vertices (0, 0, -1), (1, 0, 1) and (-1, 0, 1) has normal vector ("
		<< tr2Normal.x << ", " << tr2Normal.y << ", " << tr2Normal.z << ") and area = "
		<< tr2Area << "\n";

	const Triangle tr3 = Triangle({
		{ 0.56, 1.11, 1.23 },
		{ 0.44, -2.368, -0.54 },
		{ -1.56, 0.15, -1.92 }
	});
	const Vec3f tr3Normal = tr3.getNormalVector();
	const float tr3Area = tr3.getArea();
	std::cout << "Triangle with vertices (0.56, 1.11, 1.23), (0.44, -2.368, -0.54) and (-1.56, 0.15, -1.92) has normal vector ("
		<< tr3Normal.x << ", " << tr3Normal.y << ", " << tr3Normal.z << ") and area = "
		<< tr3Area << "\n";

	return 0;
}