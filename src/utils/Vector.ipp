// MIT License
//
// Copyright (c) 2018 Oscar B.
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.
#include <cmath>
#include <stdexcept>


namespace gvt {
	template<typename T> Vector<T>::Vector(): Vector(0, 0) {
	}

	template<typename T> Vector<T>::Vector(T x, T y) {
		this->x = x;
		this->y = y;
	}

	template<typename T> Vector<T>::Vector(T r) {
		x = cos(r);
		y = sin(r);
	}

	template<typename T> void Vector<T>::normalize() {
		double length = norm();

		if (length != 0) {
			x /= length;
			y /= length;
		}
	}

	template<typename T> void Vector<T>::rotate(double rad) {
		auto const n = norm();
		auto const theta = angle();

		x = n * cos(theta + rad);
		y = n * sin(theta + rad);
	}

	template<typename T> void Vector<T>::rotate(double rad, Vector center) {
		// partial represents the `(v - c)' vector rotated by `rad' radians
		// around the center
		auto partial = (*this - center);

		partial.rotate(rad);

		x = partial.x + center.x;
		y = partial.y + center.y;
	}

	template<typename T> double Vector<T>::norm() const {
		return sqrt(pow(x, 2) + pow(y, 2));
	}

	template<typename T>
	double Vector<T>::distance(Vector<T> const &other) const {
		return sqrt(pow(other.x - x, 2) + pow(other.y - y, 2));
	}

	template<typename T>
	Vector<T> Vector<T>::midpoint (Vector<T> const &other) const {
		return Vector<T>{(x + other.x) / 2.0, (y + other.y) / 2.0};
	}

	template<typename T> void Vector<T>::angle(double rad) {
		auto n = norm();

		x = n * cos(rad);
		y = n * sin(rad);
	}

	template<typename T> double Vector<T>::angle() const {
		return (y >= 0) ? acos(x / norm()): M_PI + acos(-x / norm());
	}

	template<typename T>
	T Vector<T>::dotProduct(Vector<T> const &other) const {
		return x * other.x + y * other.y;
	}

	template<typename T>
	double Vector<T>::projectAlong(Vector<T> const &axis) const {
		auto axisNorm = axis.norm();

		if (axisNorm != 0) {
			return dotProduct(axis) / axisNorm;
		} else {
			throw std::domain_error(
				"Can not project along a vector of length 0"
			);
		}
	}

	template<typename T>
	bool Vector<T>::within(Vector<T> topLeft, Vector<T> bottomRight) const {
		return topLeft.x < x && x < bottomRight.x && topLeft.y < y &&
				y < bottomRight.y;
	}

	template<typename T>
	Vector<T> Vector<T>::operator+ (Vector<T> const &o) const {
		return {x + o.x, y + o.y};
	}

	template<typename T>
	Vector<T> Vector<T>::operator- (Vector const &o) const {
		return {x - o.x, y - o.y};
	}

	template<typename T> Vector<T> Vector<T>::operator* (double f) const {
		return Vector(f * x, f * y);
	}

	template<typename T> Vector<T> Vector<T>::operator/ (double f) const {
		return Vector(x / f, y / f);
	}

	template<typename T>
	Vector<T>& Vector<T>::operator+= (Vector<T> const &o) {
		x += o.x;
		y += o.y;

		return *this;
	}

	template<typename T> bool Vector<T>::operator==(Vector const &o) const {
		return x == o.x && y == o.y;
	}

	template<typename T> bool Vector<T>::operator!=(Vector const &o) const {
		return x != o.x || y != o.y;
	}


	template<typename T> gvt::Vector<T> operator* (double f, gvt::Vector<T> v) {
		return gvt::Vector<T>(f * v.x, f * v.y);
	}

	template<typename T> gvt::Vector<T> operator/ (double f, gvt::Vector<T> v) {
		return gvt::Vector<T>(v.x / f, v.y / f);
	}
}


namespace std {
	template<typename T>
	size_t hash<gvt::Vector<T>>::operator() (gvt::Vector<T> const &key) const {
		// TODO Might be improved. I implemented this in a rush
		return hash<T>()(key.x) ^ hash<T>()(key.y);
	}
}
