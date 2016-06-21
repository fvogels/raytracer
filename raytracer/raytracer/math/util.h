#pragma once

#include <math.h>

struct approx
{
	double value;
	double delta;

	constexpr approx(double value, double delta = 0.00001) noexcept
		: value(value), delta(delta) { }	
};

template<typename T>
constexpr T abs(T x) noexcept
{
	return x < 0 ? -x : x;
}

constexpr bool operator ==(const approx& x, double y) noexcept
{
	return abs<double>(y - x.value) < x.delta;
}

constexpr bool operator ==(double x, const approx& y) noexcept
{
	return y == x;
}

constexpr bool operator !=(const approx& x, double y) noexcept
{
	return !(x == y);
}

constexpr bool operator !=(double x, const approx& y) noexcept
{
	return !(x == y);
}
