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
		const float length = getLength();
		if (length == 0.f) {
			return { 0.f, 0.f };
		}
		return {
			x / length,
			y / length
		};
	};

	void normalize() {
		const float length = getLength();
		if (length != 0.f) {
			x /= length;
			y /= length;
		}
	}

	Vec2f operator+(const Vec2f &rhs) const {
		return {
			x + rhs.x,
			y + rhs.y
		};
	}

	Vec2f operator-(const Vec2f &rhs) const {
		return {
			x - rhs.x,
			y - rhs.y
		};
	}

	Vec2f operator*(float scalar) const {
		return {
			x * scalar,
			y * scalar
		};
	}
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
		const float length = getLength();
		if (length == 0.f) {
			return { 0.f, 0.f, 0.f };
		}
		return {
			x / length,
			y / length,
			z / length
		};
	};

	void normalize() {
		const float length = getLength();
		if (length != 0.f) {
			x /= length;
			y /= length;
		}
	}

	Vec3f operator+(const Vec3f &rhs) const {
		return {
			x + rhs.x,
			y + rhs.y,
			z + rhs.z
		};
	}

	Vec3f operator-(const Vec3f &rhs) const {
		return {
			x - rhs.x,
			y - rhs.y,
			z - rhs.z
		};
	}

	Vec3f operator*(float scalar) const {
		return {
			x * scalar,
			y * scalar,
			z * scalar
		};
	}
};

Vec3f crossProduct(const Vec3f &lhs, const Vec3f &rhs) {
	return {
		lhs.y * rhs.z - lhs.z * rhs.y,
		lhs.z * rhs.x - lhs.x * rhs.z,
		lhs.x * rhs.y - lhs.y * rhs.x,
	};
}

float dotProduct(const Vec2f &lhs, const Vec2f &rhs) {
	return lhs.x * rhs.x + lhs.y * rhs.y;
}

float dotProduct(const Vec3f &lhs, const Vec3f &rhs) {
	return lhs.x * rhs.x + lhs.y * rhs.y + lhs.z * rhs.z;
}

struct Triangle {
	Vec3f vert0;
	Vec3f vert1;
	Vec3f vert2;

	Vec3f getNormalVector() const {
		return crossProduct(
			vert1 - vert0,
			vert2 - vert0
		).getNormal();
	}

	float getArea() const {
		return crossProduct(
			vert1 - vert0,
			vert2 - vert0
		).getLength() / 2.f;
	}
};

struct Color {
	int r;
	int g;
	int b;
};