#pragma once
#define _USE_MATH_DEFINES
#include <math.h>

namespace math
{
	class Angle final
	{
	public:
		double radians() const { return m_radians; }
		double degrees() const { return m_radians * 180 / M_PI; }

	private:
		Angle(double x) : m_radians(x) { }
		
		friend Angle operator "" _rad(long double);
		friend Angle operator "" _deg(long double);

		double m_radians;
	};

	inline Angle operator""_rad(long double x)
	{
		return Angle(x);
	}

	inline Angle operator""_deg(long double x)
	{
		return Angle(x / 180 * M_PI);
	}

	inline double sin(Angle a) { return ::sin(a.radians()); }
	inline double cos(Angle a) { return ::cos(a.radians()); }
}