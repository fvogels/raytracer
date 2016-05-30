#pragma once
#define _USE_MATH_DEFINES
#include <math.h>

namespace math
{
	class angle final
	{
	public:
		double radians() const { return m_radians; }
		double degrees() const { return m_radians * 180 / M_PI; }

	private:
		angle(double x) : m_radians(x) { }
		
		friend angle operator "" _rad(long double);
		friend angle operator "" _deg(long double);
		friend angle operator "" _°(long double);

		double m_radians;
	};

	inline angle operator""_rad(long double x)
	{
		return angle(x);
	}

	inline angle operator""_deg(long double x)
	{
		return angle(x / 180 * M_PI);
	}

	inline angle operator""_°(long double x)
	{
		return angle(x / 180 * M_PI);
	}

	inline double sin(angle a) { return ::sin(a.radians()); }
	inline double cos(angle a) { return ::cos(a.radians()); }
}