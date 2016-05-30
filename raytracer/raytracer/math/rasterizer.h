#pragma once

#include "math/rectangle2d.h"
#include "util/position.h"

namespace math
{
	class Rasterizer
	{
	private:
		rectangle2d rect;
		unsigned horizontal_subdivisions;
		unsigned vertical_subdivisions;

	public:
		Rasterizer(const rectangle2d& rect, unsigned horizontal_subdivisions, unsigned vertical_subdivisions)
			: rect(rect), horizontal_subdivisions(horizontal_subdivisions), vertical_subdivisions(vertical_subdivisions) { }

		Rasterizer(const Rasterizer&) = default;

		Rasterizer& operator =(const Rasterizer&) = default;

		rectangle2d operator [](const position&) const;
	};
}
