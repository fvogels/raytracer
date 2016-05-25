#pragma once

#include "math/subspace.h"
#include "util/position.h"

namespace math
{
	class rasteriser
	{
	private:
		subspace rect;
		unsigned horizontal_subdivisions;
		unsigned vertical_subdivisions;

	public:
		rasteriser(const subspace& rect, unsigned horizontal_subdivisions, unsigned vertical_subdivisions)
			: rect(rect), horizontal_subdivisions(horizontal_subdivisions), vertical_subdivisions(vertical_subdivisions) { }

		rasteriser(const rasteriser&) = default;

		rasteriser& operator =(const rasteriser&) = default;

		subspace operator [](const position&) const;
	};
}
