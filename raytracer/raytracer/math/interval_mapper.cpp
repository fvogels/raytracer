#include "Interval_mapper.h"

using namespace math;

double math::Interval_mapper::operator [](double x) const
{
	return to.from_relative(from.to_relative(x));
}