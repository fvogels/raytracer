#pragma once

#include "math/function.h"
#include "math/point2d.h"
#include <math.h>
#include <type_traits>

namespace math
{
	namespace functions
	{
		class HorizontalLines : public Function<bool, const Point2D&>
		{
		public:
			HorizontalLines(double thickness)
				: m_thickness(thickness)
			{
				// NOP
			}

			typename bool operator ()(const Point2D& p) const override
			{
				auto y = p.y * 10;

				return std::abs(y - std::round(y)) < m_thickness / 2;
			}

		private:
			double m_thickness;
		};
	}
}