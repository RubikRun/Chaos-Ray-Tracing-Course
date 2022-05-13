#pragma once

#include <cmath>
#include <sstream>

struct Vec2i {
	Vec2i(){}

	Vec2i(int x, int y)
		: x(x), y(y)
	{}

	int x = 0;
	int y = 0;
};

struct Vec2f {
	Vec2f(){}

	Vec2f(float x, float y)
		: x(x), y(y)
	{}

	float x = 0.f;
	float y = 0.f;

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

	Vec2f& operator+=(const Vec2f &rhs) {
		x += rhs.x;
		y += rhs.y;
		return *this;
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
	Vec3i(){}

	Vec3i(int x, int y, int z)
		: x(x), y(y), z(z)
	{}

	int x = 0;
	int y = 0;
	int z = 0;
};

struct Vec3f {
	Vec3f(){}

	Vec3f(float x, float y, float z)
		: x(x), y(y), z(z)
	{}

	float x = 0.f;
	float y = 0.f;
	float z = 0.f;

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

	Vec3f& operator+=(const Vec3f &rhs) {
		x += rhs.x;
		y += rhs.y;
		z += rhs.z;
		return *this;
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

static Vec3f crossProduct(const Vec3f &lhs, const Vec3f &rhs) {
	return {
		lhs.y * rhs.z - lhs.z * rhs.y,
		lhs.z * rhs.x - lhs.x * rhs.z,
		lhs.x * rhs.y - lhs.y * rhs.x,
	};
}

static float dotProduct(const Vec2f &lhs, const Vec2f &rhs) {
	return lhs.x * rhs.x + lhs.y * rhs.y;
}

static float dotProduct(const Vec3f &lhs, const Vec3f &rhs) {
	return lhs.x * rhs.x + lhs.y * rhs.y + lhs.z * rhs.z;
}

struct Color {
	Color(){}

	Color(int r, int g, int b)
		: r(r), g(g), b(b)
	{}

	int r = 0;
	int g = 0;
	int b = 0;
};

struct Triangle {
	Triangle(){}

	Triangle(const Vec3f &vert0, const Vec3f &vert1, const Vec3f &vert2, Color color = Color(255, 255, 255))
		: color(color)
	{
		vertices[0] = vert0;
		vertices[1] = vert1;
		vertices[2] = vert2;
	}

	Vec3f getNormalVector() const {
		return crossProduct(
			vertices[1] - vertices[0],
			vertices[2] - vertices[0]
		).getNormal();
	}

	float getArea() const {
		return crossProduct(
			vertices[1] - vertices[0],
			vertices[2] - vertices[0]
		).getLength() / 2.f;
	}

	Vec3f vertices[3];
	Color color;
};

static bool isApprox(float lhs, float rhs, float epsilon = 0.0001f) {
	return fabsf(lhs - rhs) < epsilon;
}

static bool isApproxZero(float x, float epsilon = 0.0001f) {
	return fabsf(x) < epsilon;
}

static std::string getStringFromNumber(int n, int length = -1) {
	std::stringstream sstream;
	const std::string nStr = std::to_string(n);
	if (length != -1 && nStr.length() < length) {
		for (int i = 0; i < length - nStr.length(); i++) {
			sstream << '0';
		}
	}
	sstream << nStr;
	return sstream.str();
}