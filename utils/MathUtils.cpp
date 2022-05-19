#include "MathUtils.h"

#include <cmath>

namespace MathUtils {

// Function definitions for Vec2f

float Vec2f::getLength() const {
    return sqrtf(x * x + y * y);
}

Vec2f Vec2f::getNormal() const {
    const float length = getLength();
    if (isApproxZero(length)) {
        return { 0.f, 0.f };
    }
    return { x / length, y / length };
}

void Vec2f::normalize() {
    *this = getNormal();
}

Vec2f Vec2f::operator+(const Vec2f &rhs) const {
    return { x + rhs.x, y + rhs.y };
}

Vec2f& Vec2f::operator+=(const Vec2f &rhs) {
    *this = *this + rhs;
    return *this;
}

Vec2f Vec2f::operator-(const Vec2f &rhs) const {
    return { x - rhs.x, y - rhs.y };
}

Vec2f& Vec2f::operator-=(const Vec2f &rhs) {
    *this = *this - rhs;
    return *this;
}

Vec2f Vec2f::operator*(float scalar) const {
    return { x * scalar, y * scalar };
}

Vec2f& Vec2f::operator*=(float scalar) {
    *this = *this * scalar;
    return *this;
}

// Function definitions for Vec3f

float Vec3f::getLength() const {
    return sqrtf(x * x + y * y + z * z);
}

Vec3f Vec3f::getNormal() const {
    const float length = getLength();
    if (isApproxZero(length)) {
        return { 0.f, 0.f, 0.f };
    }
    return { x / length, y / length, z / length };
}

void Vec3f::normalize() {
    *this = getNormal();
}

Vec3f Vec3f::operator+(const Vec3f &rhs) const {
    return { x + rhs.x, y + rhs.y, z + rhs.z };
}

Vec3f& Vec3f::operator+=(const Vec3f &rhs) {
    *this = *this + rhs;
    return *this;
}

Vec3f Vec3f::operator-(const Vec3f &rhs) const {
    return { x - rhs.x, y - rhs.y, z - rhs.z };
}

Vec3f& Vec3f::operator-=(const Vec3f &rhs) {
    *this = *this - rhs;
    return *this;
}

Vec3f Vec3f::operator*(float scalar) const {
    return { x * scalar, y * scalar, z * scalar };
}

Vec3f& Vec3f::operator*=(float scalar) {
    *this = *this * scalar;
    return *this;
}

// Function definitions for Matrix3f

Vec3f Matrix3f::operator*(const Vec3f &vec) const {
    return {
        xCol.x * vec.x + yCol.x * vec.y + zCol.x * vec.z,
        xCol.y * vec.x + yCol.y * vec.y + zCol.y * vec.z,
        xCol.z * vec.x + yCol.z * vec.y + zCol.z * vec.z,
    };
}

Matrix3f Matrix3f::operator*(const Matrix3f &other) const {
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

Matrix3f& Matrix3f::operator*=(const Matrix3f &other) {
    *this = *this * other;
    return *this;
}

// Global function definitions

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

Vec3f getTriangleNormal(Vec3f aVertex, Vec3f bVertex, Vec3f cVertex) {
	return crossProduct(
		bVertex - aVertex,
		cVertex - aVertex
	).getNormal();
}

float getTriangleArea(Vec3f aVertex, Vec3f bVertex, Vec3f cVertex) {
	return crossProduct(
		bVertex - aVertex,
		cVertex - aVertex
	).getLength() / 2.f;
}

bool isApprox(float lhs, float rhs, float epsilon) {
	return fabsf(lhs - rhs) < epsilon;
}

bool isApproxZero(float x, float epsilon) {
	return fabsf(x) < epsilon;
}

RayTriangleIntersectionResult rayTriangleIntersection(
    const Ray &ray,
	const Vec3f &aVert,
	const Vec3f &bVert,
	const Vec3f &cVert
) {
    // Initialize the result as if there is no intersection
    RayTriangleIntersectionResult result;

	// Normal of the triangle
	const Vec3f trNormal = getTriangleNormal(aVert, bVert, cVert);
	// Length of the ray projected on the triangle's normal.
	const float rayProj = dotProduct(ray.direction, trNormal);
	// If the ray projection on the triangle's normal is approximately zero,
	// than the ray is almost perpendicular to the triangle's plane,
	// so we don't bother to intersect it with the triangle
	if (isApproxZero(rayProj)) {
		return result;
	}

	// Distance from the ray origin to the triangle's plane, along the triangle's normal direction
	const float distToTrPlane = dotProduct(aVert - ray.origin, trNormal);

	// If the ray projection and the distance to plane have different signs,
    // then the triangle is behind the ray, so there can be no intersection
	if (rayProj * distToTrPlane < 0.f) {
		return result;
	}

	// At this point both the ray projection and distance to plane have the same sign,
	// and this sign determines whether the ray is looking at the front or the back side of the triangle
	result.frontSide = (rayProj < 0.f);

	// Calculate distance along the ray
	result.distAlongRay = distToTrPlane / rayProj;
	// Calculate the point of intersection
	result.point = ray.origin + ray.direction * result.distAlongRay;

	// Check if the point of intersection is inside the triangle.
    // If it is, then the ray does intersect the triangle.
	result.doesIntersect = (
		dotProduct(
			trNormal,
			crossProduct(bVert - aVert, result.point - aVert)
		) >= 0.f
		&&
		dotProduct(
			trNormal,
			crossProduct(cVert - bVert, result.point - bVert)
		) >= 0.f
		&&
		dotProduct(
			trNormal,
			crossProduct(aVert - cVert, result.point - cVert)
		) >= 0.f
	);

    return result;
}

} // namespace MathUtils