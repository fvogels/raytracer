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

	Point2D operator +(const Point2D&, const Vector2D&) noexcept;
	Point2D operator +(const Vector2D&, const Point2D&) noexcept;
	Vector2D operator -(const Point2D&, const Point2D&) noexcept;
	Point2D operator -(const Point2D&, const Vector2D&) noexcept;

	bool operator ==(const Point2D&, const Point2D&) noexcept;
	bool operator !=(const Point2D&, const Point2D&) noexcept;

	double distance(const Point2D&, const Point2D&) noexcept;

	std::ostream& operator <<(std::ostream& out, const Point2D&);
}
