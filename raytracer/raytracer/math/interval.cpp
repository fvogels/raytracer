#include "interval.h"

using namespace math;

double math::interval::size() const
{
	return upper - lower;
}

bool math::interval::contains(double x) const
{
	return lower <= x && x <= upper;
}

double math::interval::to_relative(double x) const
{
	return (x - lower) / size();
}

double math::interval::from_relative(double t) const
{
	return t * size() + lower;
}