#include "interval_mapper.h"

using namespace math;

double math::IntervalMapper::operator [](double x) const
{
	return to.from_relative(from.to_relative(x));
}