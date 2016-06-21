#pragma once

#include <iostream>
#include "math/util.h"


namespace math
{
	struct Vector2D final
	{
		double x, y;

		constexpr Vector2D() noexcept
			: x(0), y(0) { }

		constexpr Vector2D(double x, double y) noexcept
			: x(x), y(y) { }

		constexpr Vector2D(const Vector2D& v) noexcept = default;

		Vector2D& operator =(const Vector2D&) noexcept = default;

		constexpr double dot(const Vector2D&) const noexcept;

		constexpr double norm_sqr() const noexcept;
		double norm() const noexcept;
		void normalize() noexcept;
		Vector2D normalized() const noexcept;
		bool is_unit() const noexcept;

		Vector2D& operator +=(const Vector2D&) noexcept;
		Vector2D& operator -=(const Vector2D&) noexcept;
		Vector2D& operator *=(double) noexcept;
		Vector2D& operator /=(double) noexcept;

		constexpr bool is_perpendicular_on(const Vector2D&) const noexcept;
	};

	constexpr Vector2D operator +(const Vector2D& u, const Vector2D& v) noexcept
	{
		return Vector2D(u.x + v.x, u.y + v.y);
	}

	constexpr Vector2D operator -(const Vector2D& v) noexcept
	{
		return Vector2D(-v.x, -v.y);
	}

	constexpr Vector2D operator -(const Vector2D& u, const Vector2D& v) noexcept
	{
		return Vector2D(u.x - v.x, u.y - v.y);
	}

	constexpr Vector2D operator *(const Vector2D& v, double factor) noexcept
	{
		return Vector2D(v.x * factor, v.y * factor);
	}

	constexpr Vector2D operator *(double factor, const Vector2D& v) noexcept
	{
		return v * factor;
	}

	constexpr Vector2D operator /(const Vector2D& v, double factor) noexcept
	{
		return v * (1.0 / factor);
	}

	constexpr bool operator ==(const Vector2D& u, const Vector2D& v) noexcept
	{
		return u.x == approx(v.x) && u.y == approx(v.y);
	}

	constexpr bool operator !=(const Vector2D& u, const Vector2D& v) noexcept
	{
		return !(u == v);
	}

	std::ostream& operator <<(std::ostream& out, const Vector2D&);
}