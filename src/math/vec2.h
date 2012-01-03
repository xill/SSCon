#ifndef VEC2_H
#define VEC2_H

#include "math/math.h"

/**
 * 2D column vector.
 */
template <typename T>
struct Vec2
{
	T x;
	T y;

	Vec2() : x(0), y(0) {}
	Vec2(T x, T y) : x(x), y(y) {}

	void setZero() {
		x = 0;
		y = 0;
	}

	bool isZero() {
		return x == 0 && y == 0;
	}

	void set(T x, T y) {
		this->x = x;
		this->y = y;
	}

	Vec2<T> &operator+=(const Vec2<T> &rhs) {
		x += rhs.x;
		y += rhs.y;
		return *this;
	}

	Vec2<T> operator+(const Vec2<T> &rhs) const {
		return Vec2<T>(*this)+=rhs;
	}

	Vec2<T> &operator+=(T rhs) {
		x += rhs;
		y += rhs;
		return *this;
	}

	Vec2<T> operator+(T rhs) const {
		return Vec2<T>(*this)+=rhs;
	}

	Vec2<T> &operator-=(const Vec2<T> &rhs) {
		x -= rhs.x;
		y -= rhs.y;
		return *this;
	}

	Vec2<T> operator-(const Vec2<T> &rhs) const {
		return Vec2<T>(*this)-=rhs;
	}

	Vec2<T> operator-() const{
		return Vec2<T>(-this->x, -this->y);
	}

	Vec2<T> &operator*=(const Vec2<T> &rhs) {
		x *= rhs.x;
		y *= rhs.y;
		return *this;
	}

	Vec2<T> operator*(const Vec2<T> &rhs) const {
		return Vec2<T>(*this)*=rhs;
	}

	Vec2<T> &operator*=(T factor) {
		 x *= factor;
		 y *= factor;
		 return *this;
	}

	Vec2<T> operator*(T factor) const {
		return Vec2<T>(*this)*=(factor);
	}

	Vec2<T> &operator/=(const Vec2<T> &rhs) {
		x /= rhs.x;
		y /= rhs.y;
		return *this;
	}

	Vec2<T> operator/(const Vec2<T> &rhs) const {
		return Vec2<T>(*this)/=rhs;
	}

	Vec2<T> &operator/=(T factor) {
		 x /= factor;
		 y /= factor;
		 return *this;
	}

	Vec2<T> operator/(T factor) const {
		return Vec2<T>(*this)/=(factor);
	}

	/**
	 * This actually compares the length of the vector to a scalar number
	 * so dont get confused. Basically the idea is to avoid sqrt.
	 */
	bool operator<(T rhs) const {
		if (x > rhs || y > rhs){
			return false;
		}
		return this->length() < rhs;
	}

	/**
	 * Returns the length of the vector.
	 *
	 * @return length of the vector.
	 */
	T length() const {
		return sqrt(x*x + y*y);
	}

	/**
	 * Returns the length of the vector squared.
	 * Use this for perfomance.
	 *
	 * @return length of the vector squared.
	 */
	T lengthSquared() const {
		return x*x + y*y;
	}

	/**
	 * Returns a merged Vec2<T> from the min values from a and b.
	 *
	 * @param a
	 * @param b
	 *
	 * @returns merged min Vec2<T>
	 */
	static Vec2<T> min(const Vec2<T> &a, const Vec2<T> &b) {
		return Vec2<T>(std::min(a.x, b.x), std::min(a.y, b.y));
	}

	/**
	 * Returns a merged Vec2<T> from the max values from a and b.
	 *
	 * @param a
	 * @param b
	 *
	 * @returns merged max Vec2<T>
	 */
	static Vec2<T> max(const Vec2<T> &a, const Vec2<T> &b) {
		return Vec2<T>(std::max(a.x, b.x), std::max(a.y, b.y));
	}

	/**
	 * Compute the dot-product.
	 *
	 * @param rhs
	 *
	 * @return value of dot-product.
	 */
	T dot(const Vec2<T> &rhs) const {
		return x*rhs.x + y*rhs.y;
	}

	/**
	 * Compute the cross-product.
	 *
	 * @param rhs
	 *
	 * @return value of cross-product
	 */
	T cross(const Vec2<T> &rhs) const {
		return (x * rhs.y) - (y * rhs.x);
	}

	/**
	 * Rotate *this around origin by given degrees.
	 *
	 * @param degrees to rotate
	 */
	void rotateDegrees(T degrees) {
		this->rotateRadians(degrees * DEGREES_2_RADIANS);
	}

	/**
	 * Rotate *this around origin by given radians.
	 *
	 * @param radians to rotate
	 */
	void rotateRadians(T radians) {
		T tmp_x = x;
		x = tmp_x * std::cos(radians) - y * std::sin(radians);
		y = tmp_x * std::sin(radians) + y * std::cos(radians);
	}

};

typedef Vec2<int>    Vec2i;
typedef Vec2<float>  Vec2f;
typedef Vec2<double> Vec2d;

#endif // VEC2_H
