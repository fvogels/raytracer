#pragma once

#include "math/vector2d.h"
#include "math/util.h"


namespace math
{
	struct Point2D final
	{
		double x, y;

		constexpr Point2D() noexcept
			: x(0), y(0) { }

		constexpr Point2D(double x, double y) noexcept
			: x(x), y(y) { }

		constexpr Point2D(const Point2D& v) noexcept = default;

		Point2D& operator =(const Point2D&) noexcept = default;
	};

	constexpr Point2D operator +(const Point2D& p, const Vector2D& v) noexcept
	{
		return Point2D(p.x + v.x, p.y + v.y);
	}

	constexpr Point2D operator +(const Vector2D& v, const Point2D& p) noexcept
	{
		return p + v;
	}

	constexpr Vector2D operator -(const Point2D& p, const Point2D& q) noexcept
	{
		return Vector2D(p.x - q.x, p.y - q.y);
	}

	constexpr Point2D operator -(const Point2D& p, const Vector2D& v) noexcept
	{
		return Point2D(p.x - v.x, p.y - v.y);
	}

	constexpr bool operator ==(const Point2D& p, const Point2D& q) noexcept
	{
		return p.x == approx(q.x) && p.y == approx(q.y);
	}

	constexpr bool operator !=(const Point2D& p, const Point2D& q) noexcept
	{
		return !(p == q);
	}

	double distance(const Point2D&, const Point2D&) noexcept;

	std::ostream& operator <<(std::ostream& out, const Point2D&);
}
