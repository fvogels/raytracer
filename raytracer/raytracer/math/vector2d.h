#pragma once

#include <iostream>

namespace math
{
	struct Vector2D final
	{
		double x, y;

		Vector2D()
			: x(0), y(0) { }

		Vector2D(double x, double y)
			: x(x), y(y) { }

		Vector2D(const Vector2D& v) = default;

		Vector2D& operator =(const Vector2D&) = default;

		double dot(const Vector2D&) const;

		double norm_sqr() const;
		double norm() const;
		void normalize();
		Vector2D normalized() const;
		bool is_unit() const;

		Vector2D& operator +=(const Vector2D&);
		Vector2D& operator -=(const Vector2D&);
		Vector2D& operator *=(double);
		Vector2D& operator /=(double);

		bool is_perpendicular_on(const Vector2D&) const;
	};

	Vector2D operator +(const Vector2D&, const Vector2D&);
	Vector2D operator -(const Vector2D&);
	Vector2D operator -(const Vector2D&, const Vector2D&);
	Vector2D operator *(const Vector2D&, double factor);
	Vector2D operator *(double factor, const Vector2D&);
	Vector2D operator /(const Vector2D&, double factor);

	bool operator ==(const Vector2D&, const Vector2D&);
	bool operator !=(const Vector2D&, const Vector2D&);

	std::ostream& operator <<(std::ostream& out, const Vector2D&);
}