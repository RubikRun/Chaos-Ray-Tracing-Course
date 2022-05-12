#include "utils.hpp"

#include <iostream>

int main() {
	const Vec3f ans1 = crossProduct({ 3.5f, 0.f, 0.f }, { 1.75f, 3.5f, 0.f });
	std::cout << "Cross product of (3.5, 0, 0) and (1.75, 3.5, 0) is ("
		<< ans1.x << ", " << ans1.y << ", " << ans1.z << ")\n";

	const Vec3f ans2 = crossProduct({ 3.f, -3.f, 1.f }, { 4.f, 9.f, 3.f });
	std::cout << "Cross product of (3, -3, 1) and (4, 9, 3) is ("
		<< ans2.x << ", " << ans2.y << ", " << ans2.z << ")\n";

	const float ans3 = crossProduct({ 3.f, -3.f, 1.f }, { 4.f, 9.f, 3.f }).getLength();
	std::cout << "Area of parallelogram with vectors (3, -3, 1) and (4, 9, 3) is "
		<< ans3 << "\n";

	// Second vector is just first vector scaled so cross product is the zero vector and area is zero
	const float ans4 = crossProduct({ 3.f, -3.f, 1.f }, { -12.f, 12.f, -4.f }).getLength();
	std::cout << "Area of parallelogram with vectors (3, -3, 1) and (-12, 12, -4) is "
		<< ans4 << "\n";

	return 0;
}