#pragma once

#include "math/rectangle2D.h"
#include "util/position.h"

namespace math
{
	class Rasterizer
	{
	private:
		Rectangle2D rect;
		unsigned horizontal_subdivisions;
		unsigned vertical_subdivisions;

	public:
		Rasterizer(const Rectangle2D& rect, unsigned horizontal_subdivisions, unsigned vertical_subdivisions)
			: rect(rect), horizontal_subdivisions(horizontal_subdivisions), vertical_subdivisions(vertical_subdivisions) { }

		Rasterizer(const Rasterizer&) = default;

		Rasterizer& operator =(const Rasterizer&) = default;

		Rectangle2D operator [](const position&) const;
	};
}
