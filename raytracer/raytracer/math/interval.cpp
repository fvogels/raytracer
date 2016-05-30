#include "Interval.h"

using namespace math;

double math::Interval::size() const
{
	return upper - lower;
}

bool math::Interval::contains(double x) const
{
	return lower <= x && x <= upper;
}

double math::Interval::to_relative(double x) const
{
	return (x - lower) / size();
}

double math::Interval::from_relative(double t) const
{
	return t * size() + lower;
}