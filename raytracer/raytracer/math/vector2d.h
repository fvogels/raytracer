#pragma once

#include <iostream>
#include "math/util.h"


namespace math
{
	struct Vector2D final
	{
		double x, y;

		Vector2D() noexcept
			: x(0), y(0) { }

		Vector2D(double x, double y) noexcept
			: x(x), y(y) { }

		Vector2D(const Vector2D& v) noexcept = default;

		Vector2D& operator =(const Vector2D&) noexcept = default;

		double dot(const Vector2D&) const noexcept;

		double norm_sqr() const noexcept;
		double norm() const noexcept;
		void normalize() noexcept;
		Vector2D normalized() const noexcept;
		bool is_unit() const noexcept;

		Vector2D& operator +=(const Vector2D&) noexcept;
		Vector2D& operator -=(const Vector2D&) noexcept;
		Vector2D& operator *=(double) noexcept;
		Vector2D& operator /=(double) noexcept;

		bool is_perpendicular_on(const Vector2D&) const noexcept;
	};

	Vector2D operator +(const Vector2D&, const Vector2D&) noexcept;
	Vector2D operator -(const Vector2D&) noexcept;
	Vector2D operator -(const Vector2D&, const Vector2D&) noexcept;
	Vector2D operator *(const Vector2D&, double) noexcept;
	Vector2D operator *(double, const Vector2D&) noexcept;
	Vector2D operator /(const Vector2D&, double) noexcept;

	bool operator ==(const Vector2D&, const Vector2D&) noexcept;
	bool operator !=(const Vector2D&, const Vector2D&) noexcept;

	std::ostream& operator <<(std::ostream& out, const Vector2D&);
}