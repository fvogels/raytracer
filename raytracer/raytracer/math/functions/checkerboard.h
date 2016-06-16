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
		class Checkerboard : public Function<typename T::result, const Point2D&>
		{
		public:
			Checkerboard(T converter = T())
				: m_converter(converter)
			{
				// NOP
			}

			typename T::result operator ()(const Point2D& p) const override
			{
				double x = p.x - std::floor(p.x);
				double y = p.y - std::floor(p.y);

				return m_converter((x < 0.5) != (y < 0.5));
			}

		private:
			T m_converter;
		};
	}
}