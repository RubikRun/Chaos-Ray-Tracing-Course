#pragma once

namespace MathUtils {

/// Vector of 2 integer coordinates
struct Vec2i {
    /// Creates a zero vector
	Vec2i(){}

    /// Creates a vector with some coordinates
	Vec2i(int x, int y)
		: x(x), y(y)
	{}

    /// X and Y coordinates of the vector
	int x = 0;
	int y = 0;
};

/// Vector of 2 float coordinates
struct Vec2f {
    /// Creates a zero vector
	Vec2f(){}

    /// Creates a vector with some coordinates
	Vec2f(float x, float y)
		: x(x), y(y)
	{}

    /// X and Y coordinates of the vector
	float x = 0.f;
	float y = 0.f;

    /// Calculates the length of the vector
	float getLength() const;
    /// Returns the vector normalized, with unit length
	Vec2f getNormal() const;
    /// Normalizes the vector, changes it to have unit length
	void normalize();
    /// Returns the sum of this vector and another vector
	Vec2f operator+(const Vec2f &rhs) const;
    /// Adds another vector to this vector
	Vec2f& operator+=(const Vec2f &rhs);
    /// Returns the difference of this vector and another vector
	Vec2f operator-(const Vec2f &rhs) const;
    /// Subtracts another vector from this vector
	Vec2f& operator-=(const Vec2f &rhs);
    /// Returns the result of scaling this vector by a number
	Vec2f operator*(float scalar) const;
    /// Returns the result of scaling this vector by a number
	Vec2f& operator*=(float scalar);
};

/// Vector of 3 integer coordinates
struct Vec3i {
    /// Creates a zero vector
	Vec3i(){}

    /// Creates a vector with some coordinates
	Vec3i(int x, int y, int z)
		: x(x), y(y), z(z)
	{}

    /// X, Y and Z coordinates of the vector
	int x = 0;
	int y = 0;
	int z = 0;
};

/// Vector of 3 float coordinates
struct Vec3f {
    /// Creates a zero vector
	Vec3f(){}

    /// Creates a vector with some coordinates
	Vec3f(float x, float y, float z)
		: x(x), y(y), z(z)
	{}

    /// X, Y and Z coordinates of the vector
	float x = 0.f;
	float y = 0.f;
    float z = 0.f;

    /// Calculates the length of the vector
	float getLength() const;
    /// Returns the vector normalized, with unit length
	Vec3f getNormal() const;
    /// Normalizes the vector, changes it to have unit length
	void normalize();
    /// Returns the sum of this vector and another vector
	Vec3f operator+(const Vec3f &rhs) const;
    /// Adds another vector to this vector
	Vec3f& operator+=(const Vec3f &rhs);
    /// Returns the difference of this vector and another vector
	Vec3f operator-(const Vec3f &rhs) const;
    /// Subtracts another vector from this vector
	Vec3f& operator-=(const Vec3f &rhs);
    /// Returns the result of scaling this vector by a number
	Vec3f operator*(float scalar) const;
    /// Returns the result of scaling this vector by a number
	Vec3f& operator*=(float scalar);
};

/// Colors are represented with 3 floats - Red, Blue and Green with values in range [0, 1]
typedef Vec3f Color;

/// Ray in 3D space.
struct Ray {
	/// Origin of the ray, a point in world space
	Vec3f origin;
	/// Direction of the ray, a normal vector
	Vec3f direction;
};

/// 3 by 3 matrix with float entries
struct Matrix3f {
    /// Creates an identity matrix
	Matrix3f(){}

    /// Creates a matrix with given vectors for the columns of the matrix
	Matrix3f(const Vec3f &xCol, const Vec3f &yCol, const Vec3f &zCol)
		: xCol(xCol), yCol(yCol), zCol(zCol)
	{}

    /// Entries of the matrix,
    /// represented as 3 vectors, one for each column of the matrix.
    /// This way the unit vectors X, Y and Z map to xCol, yCol and zCol
    /// under the matrix's transformation.
	Vec3f xCol = { 1.f, 0.f, 0.f };
	Vec3f yCol = { 0.f, 1.f, 0.f };
	Vec3f zCol = { 0.f, 0.f, 1.f };

    /// Transforms a vector with the matrix, returns the resulting vector
	Vec3f operator*(const Vec3f &vec) const;
    /// Returns the result from multiplying this matrix by another matrix.
    /// The resulting matrix acts as applying first the other matrix, and then this matrix.
	Matrix3f operator*(const Matrix3f &other) const;
    /// Multiplies this matrix by another matrix.
    Matrix3f& operator*=(const Matrix3f &other);
};

/// Computes the cross product of two 3D vectors
Vec3f crossProduct(const Vec3f &lhs, const Vec3f &rhs);

/// Computes the dot product of two 2D vectors
float dotProduct(const Vec2f &lhs, const Vec2f &rhs);

/// Computes the dot product of two 3D vectors
float dotProduct(const Vec3f &lhs, const Vec3f &rhs);

/// Computes the normal vector of a triangle represented with its 3 vertices as points in world space.
Vec3f getTriangleNormal(Vec3f aVertex, Vec3f bVertex, Vec3f cVertex);

/// Computes the area of a triangle represented with its 3 vertices as points in world space.
float getTriangleArea(Vec3f aVertex, Vec3f bVertex, Vec3f cVertex);

/// Checks if 2 float values are approximately equal.
/// Optionally an epsilon can be specified for the comparison.
bool isApprox(float lhs, float rhs, float epsilon = 0.0001f);

/// Checks if a float value is approximately equal to 0.
/// Optionally an epsilon can be specified for the comparison.
bool isApproxZero(float x, float epsilon = 0.0001f);

/// Returns the minimum of 2 values
template <typename T>
T getMin(T a, T b) {
	return (a < b) ? a : b;
}

/// Returns the maximum of 2 values
template <typename T>
T getMax(T a, T b) {
	return (a > b) ? a : b;
}

/// Result of an intersection between a ray and a triangle
struct RayTriangleIntersectionResult {
    /// Point of intersection
    Vec3f point = { 0.f, 0.f, 0.f };
    /// Distance along the ray where the intersection happened
    float distAlongRay = -1.f;
    /// Indicates whether there was an intersection
    bool doesIntersect = false;
    /// Indicates whether the intersection happened through the front or the back side of the triangle
    bool frontSide = true;
};

/// Intersects a ray with a triangle.
/// Checks if the ray intersects the triangle and if it does, finds the intersection point.
/// @param[in] aVert, bVert, cVert The vertices of the triangle to be intersected
/// @param[in] ray The ray to intersect with
/// @return The result of the ray triangle intersection
RayTriangleIntersectionResult rayTriangleIntersection(
    const Ray &ray,
	const Vec3f &aVert,
	const Vec3f &bVert,
	const Vec3f &cVert
);

} // namespace MathUtils