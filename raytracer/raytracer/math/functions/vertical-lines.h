#pragma once

#include "math/function.h"
#include "math/point2d.h"
#include <math.h>
#include <type_traits>

namespace math
{
	namespace functions
	{
		template<typename T>
		class VerticalLines : public Function<typename T::result, const Point2D&>
		{
		public:
			VerticalLines(double thickness, T converter = T())
				: m_thickness(thickness), m_converter(converter)
			{
				// NOP
			}

			typename T::result operator ()(const Point2D& p) const override
			{
				auto x = p.x * 10;
				return m_converter(std::abs(x - std::round(x)) < m_thickness / 2);
			}

		private:
			double m_thickness;
			T m_converter;
		};
	}
}