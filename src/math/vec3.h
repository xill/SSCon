#ifndef VEC3_H
#define VEC3_H

#include "math/math.h"

/**
 * 3D column vector.
 */
template <typename T>
struct Vec3
{
	T x;
	T y;
	T z;

	Vec3() : x(0), y(0), z(0) {}
	Vec3(T x, T y, T z) : x(x), y(y), z(z) {}

	void setZero() {
		x = 0;
		y = 0;
		z = 0;
	}

	bool isZero() {
		return x == 0 && y == 0 && z == 0;
	}

	void set(T x, T y, T z) {
		this->x = x;
		this->y = y;
		this->z = z;
	}

	Vec3<T> &operator+=(const Vec3<T> &rhs) {
		x += rhs.x;
		y += rhs.y;
		z += rhs.z;
		return *this;
	}

	Vec3<T> operator+(const Vec3<T> &rhs) const {
		return Vec3<T>(*this)+=rhs;
	}

	Vec3<T> &operator+=(T rhs) {
		x += rhs;
		y += rhs;
		z += rhs;
		return *this;
	}

	Vec3<T> operator+(T rhs) const {
		return Vec3<T>(*this)+=rhs;
	}

	Vec3<T> &operator-=(const Vec3<T> &rhs) {
		x -= rhs.x;
		y -= rhs.y;
		z -= rhs.z;
		return *this;
	}

	Vec3<T> operator-(const Vec3<T> &rhs) const {
		return Vec3<T>(*this)-=rhs;
	}

	Vec3<T> operator-() const {
		return Vec3<T>(-this->x, -this->y, -this->z);
	}

	Vec3<T> &operator*=(const Vec3<T> &rhs) {
		x *= rhs.x;
		y *= rhs.y;
		z *= rhs.z;
		return *this;
	}

	Vec3<T> operator*(const Vec3<T> &rhs) const {
		return Vec3<T>(*this)*=rhs;
	}

	Vec3<T> &operator*=(T factor) {
		 x *= factor;
		 y *= factor;
		 z *= factor;
		 return *this;
	}

	Vec3<T> operator*(T factor) const {
		return Vec3<T>(*this)*=(factor);
	}

	Vec3<T> &operator/=(const Vec3<T> &rhs) {
		x /= rhs.x;
		y /= rhs.y;
		z /= rhs.z;
		return *this;
	}

	Vec3<T> operator/(const Vec3<T> &rhs) const {
		return Vec3<T>(*this)/=rhs;
	}

	Vec3<T> &operator/=(T factor) {
		 x /= factor;
		 y /= factor;
		 z /= factor;
		 return *this;
	}

	Vec3<T> operator/(T factor) const {
		return Vec3<T>(*this)/=(factor);
	}

	/**
	 * Returns the length of the vector.
	 *
	 * @return length of the vector.
	 */
	T length() const {
		return sqrt(x*x + y*y + z*z);
	}

	/**
	 * Returns the length of the vector squared.
	 * Use this for perfomance.
	 *
	 * @return length of the vector squared.
	 */
	T lengthSquared() const {
		return x*x + y*y * z*z;
	}

	/**
	 * Returns a merged Vec3<T> from the min values from a and b.
	 *
	 * @param a
	 * @param b
	 *
	 * @returns merged min Vec3<T>
	 */
	static Vec3<T> min(const Vec3<T> &a, const Vec3<T> &b) {
		return Vec3<T>(
			std::min(a.x, b.x),
			std::min(a.y, b.y),
			std::min(a.z, b.z));
	}

	/**
	 * Returns a merged Vec3<T> from the max values from a and b.
	 *
	 * @param a
	 * @param b
	 *
	 * @returns merged max Vec3<T>
	 */
	static Vec3<T> max(const Vec3<T> &a, const Vec3<T> &b) {
		return Vec3<T>(
			std::max(a.x, b.x),
			std::max(a.y, b.y),
			std::max(a.z, b.z));
	}

	/**
	 * Compute the dot-product.
	 *
	 * @param rhs
	 *
	 * @return value of dot-product.
	 */
	T dot(const Vec3<T> &rhs) const {
		return x*rhs.x + y*rhs.y + z*rhs.z;
	}

	Vec3<T> cross(const Vec3<T> &rhs) const {
		return Vec3<T>(
			y*rhs.z - z*rhs.y,
			z*rhs.x - x*rhs.z,
			x*rhs.y - y*rhs.x);
	}

};

typedef Vec3<int>    Vec3i;
typedef Vec3<float>  Vec3f;
typedef Vec3<double> Vec3d;

#endif // VEC3_H
