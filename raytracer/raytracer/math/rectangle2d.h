#pragma once

#include "math/vector2d.h"
#include "math/point2D.h"

namespace math
{
	struct Rectangle2D
	{
		Point2D origin;
		vector2d x_axis;
		vector2d y_axis;

		Rectangle2D(const Point2D& origin, const vector2d& x_axis, const vector2d& y_axis)
			: origin(origin), x_axis(x_axis), y_axis(y_axis) { }

		Point2D center() const;
	};

	bool operator ==(const Rectangle2D&, const Rectangle2D&);
	bool operator !=(const Rectangle2D&, const Rectangle2D&);
}