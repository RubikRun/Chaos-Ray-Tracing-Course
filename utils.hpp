#pragma once

#include <cmath>

struct Vec2i {
	int x;
	int y;
};

struct Vec2f {
	float x;
	float y;

	float getLength() const {
		return sqrtf(x * x + y * y);
	}

	Vec2f getNormal() const {
		return {
			x / getLength(),
			y / getLength()
		};
	};
};

struct Vec3i {
	int x;
	int y;
	int z;
};

struct Vec3f {
	float x;
	float y;
	float z;

	float getLength() const {
		return sqrtf(x * x + y * y + z * z);
	}

	Vec3f getNormal() const {
		return {
			x / getLength(),
			y / getLength(),
			z / getLength()
		};
	};
};

struct Color {
	int r;
	int g;
	int b;
};