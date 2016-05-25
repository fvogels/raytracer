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