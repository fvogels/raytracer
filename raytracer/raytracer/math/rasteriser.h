#pragma once

#include "math/rectangle3d.h"
#include "util/position.h"

namespace math
{
	class rasteriser
	{
	private:
		rectangle3d rect;
		unsigned horizontal_subdivisions;
		unsigned vertical_subdivisions;

	public:
		rasteriser(const rectangle3d& rect, unsigned horizontal_subdivisions, unsigned vertical_subdivisions)
			: rect(rect), horizontal_subdivisions(horizontal_subdivisions), vertical_subdivisions(vertical_subdivisions) { }

		rasteriser(const rasteriser&) = default;

		rasteriser& operator =(const rasteriser&) = default;

		rectangle3d operator [](const position&) const;
	};
}
