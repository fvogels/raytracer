#pragma once

#include "math/function.h"
#include "math/point2d.h"
#include <math.h>
#include <type_traits>

namespace math
{
	namespace functions
	{
		class VerticalLines : public Function<bool, const Point2D&>
		{
		public:
			VerticalLines(double thickness)
				: m_thickness(thickness)
			{
				// NOP
			}

			typename bool operator ()(const Point2D& p) const override
			{
				auto x = p.x * 10;
				return std::abs(x - std::round(x)) < m_thickness / 2;
			}

		private:
			double m_thickness;
		};
	}
}