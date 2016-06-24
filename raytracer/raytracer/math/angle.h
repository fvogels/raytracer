#pragma once
#define _USE_MATH_DEFINES
#include <math.h>

namespace math
{
	class Angle final
	{
	public:
		constexpr double radians() const noexcept { return m_radians; }
		constexpr double degrees() const noexcept { return m_radians * 180 / M_PI; }

		Angle operator+(const Angle& x) const noexcept { return math::radians(this->radians() + x.radians()); }
		Angle operator-() const noexcept { return Angle(-m_radians); }
		Angle operator-(const Angle& x) const noexcept { return math::radians(this->radians() - x.radians()); }

	private:
		constexpr explicit Angle(double x) noexcept
			: m_radians(x) { }
		
		friend constexpr Angle radians(long double) noexcept;
		friend constexpr Angle degrees(long double) noexcept;
		
		double m_radians;
	};

	constexpr Angle radians(long double x) noexcept
	{
		return Angle(x);
	}

	constexpr Angle degrees(long double x) noexcept
	{
		return Angle(x / 180 * M_PI);
	}

	constexpr Angle operator""_rad(long double x) noexcept
	{
		return radians(x);
	}

	constexpr Angle operator""_degrees(long double x) noexcept
	{
		return degrees(x);
	}

	constexpr Angle operator""_rad(long long unsigned x) noexcept
	{
		return radians(long double(x));
	}

	constexpr Angle operator""_degrees(long long unsigned x) noexcept
	{
		return degrees(long double(x));
	}

	constexpr Angle operator *(const Angle& angle, double factor) noexcept
	{
		return radians(angle.radians() * factor);
	}

	constexpr Angle operator *(double factor, const Angle& angle) noexcept
	{
		return angle * factor;
	}

	inline double sin(Angle a) { return ::sin(a.radians()); }
	inline double cos(Angle a) { return ::cos(a.radians()); }
}