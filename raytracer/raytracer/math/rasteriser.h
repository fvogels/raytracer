#pragma once

#include "math/rectangle2d.h"
#include "util/position.h"

namespace math
{
	class rasteriser
	{
	private:
		rectangle2d rect;
		unsigned horizontal_subdivisions;
		unsigned vertical_subdivisions;

	public:
		rasteriser(const rectangle2d& rect, unsigned horizontal_subdivisions, unsigned vertical_subdivisions)
			: rect(rect), horizontal_subdivisions(horizontal_subdivisions), vertical_subdivisions(vertical_subdivisions) { }

		rasteriser(const rasteriser&) = default;

		rasteriser& operator =(const rasteriser&) = default;

		rectangle2d operator [](const position&) const;
	};
}
