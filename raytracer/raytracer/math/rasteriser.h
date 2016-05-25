#pragma once

#include "math/rectangle.h"
#include "util/position.h"

namespace math
{
	class rasteriser
	{
	private:
		rectangle rect;
		unsigned horizontal_subdivisions;
		unsigned vertical_subdivisions;

	public:
		rasteriser(const rectangle& rect, unsigned horizontal_subdivisions, unsigned vertical_subdivisions)
			: rect(rect), horizontal_subdivisions(horizontal_subdivisions), vertical_subdivisions(vertical_subdivisions) { }

		rasteriser(const rasteriser&) = default;

		rasteriser& operator =(const rasteriser&) = default;

		rectangle operator [](const position&) const;
	};
}
