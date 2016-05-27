#pragma once

#include <math.h>

struct approx
{
	double value;

	approx(double value) : value(value) { }	
};

inline bool operator ==(approx x, double y)
{
	return fabs(y - x.value) < 0.00001;
}

inline bool operator ==(double x, approx y)
{
	return y == x;
}