#pragma once

#include <math.h>

struct approx
{
	double value;
	double delta;

	approx(double value, double delta = 0.00001) 
		: value(value), delta(delta) { }	
};

inline bool operator ==(const approx& x, double y)
{
	return fabs(y - x.value) < x.delta;
}

inline bool operator ==(double x, const approx& y)
{
	return y == x;
}

inline bool operator !=(const approx& x, double y)
{
	return !(x == y);
}

inline bool operator !=(double x, const approx& y)
{
	return !(x == y);
}
