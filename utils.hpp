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

struct Matrix3f {
	Matrix3f(){}

	Matrix3f(const Vec3f &xCol, const Vec3f &yCol, const Vec3f &zCol)
		: xCol(xCol), yCol(yCol), zCol(zCol)
	{}

	Vec3f xCol = { 1.f, 0.f, 0.f };
	Vec3f yCol = { 0.f, 1.f, 0.f };
	Vec3f zCol = { 0.f, 0.f, 1.f };

	Vec3f operator*(const Vec3f &vec) const {
		return {
			xCol.x * vec.x + yCol.x * vec.y + zCol.x * vec.z,
			xCol.y * vec.x + yCol.y * vec.y + zCol.y * vec.z,
			xCol.z * vec.x + yCol.z * vec.y + zCol.z * vec.z,
		};
	}

	Matrix3f operator*(const Matrix3f &other) const {
		return Matrix3f(
			{
				xCol.x * other.xCol.x + yCol.x * other.xCol.y + zCol.x * other.xCol.z,
				xCol.y * other.xCol.x + yCol.y * other.xCol.y + zCol.y * other.xCol.z,
				xCol.z * other.xCol.x + yCol.z * other.xCol.y + zCol.z * other.xCol.z,
			},
			{
				xCol.x * other.yCol.x + yCol.x * other.yCol.y + zCol.x * other.yCol.z,
				xCol.y * other.yCol.x + yCol.y * other.yCol.y + zCol.y * other.yCol.z,
				xCol.z * other.yCol.x + yCol.z * other.yCol.y + zCol.z * other.yCol.z,
			},
			{
				xCol.x * other.zCol.x + yCol.x * other.zCol.y + zCol.x * other.zCol.z,
				xCol.y * other.zCol.x + yCol.y * other.zCol.y + zCol.y * other.zCol.z,
				xCol.z * other.zCol.x + yCol.z * other.zCol.y + zCol.z * other.zCol.z,
			}
		);
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

	Color(float r, float g, float b)
		: r(r), g(g), b(b)
	{}

	float r = 0.f;
	float g = 0.f;
	float b = 0.f;
};

static Vec3f getTriangleNormal(Vec3f aVertex, Vec3f bVertex, Vec3f cVertex) {
	return crossProduct(
		bVertex - aVertex,
		cVertex - aVertex
	).getNormal();
}

static float getTriangleArea(Vec3f aVertex, Vec3f bVertex, Vec3f cVertex) {
	return crossProduct(
		bVertex - aVertex,
		cVertex - aVertex
	).getLength() / 2.f;
}

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