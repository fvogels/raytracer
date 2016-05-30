#pragma once

#include "math/vector2d.h"

namespace math
{
	struct Point2D final
	{
		double x, y;

		Point2D()
			: x(0), y(0) { }

		Point2D(double x, double y)
			: x(x), y(y) { }

		Point2D(const Point2D& v) = default;

		Point2D& operator =(const Point2D&) = default;
	};

	Point2D operator +(const Point2D&, const vector2d&);
	Point2D operator +(const vector2d&, const Point2D&);
	vector2d operator -(const Point2D&, const Point2D&);
	Point2D operator -(const Point2D&, const vector2d&);

	bool operator ==(const Point2D&, const Point2D&);
	bool operator !=(const Point2D&, const Point2D&);

	double distance(const Point2D&, const Point2D&);
}
