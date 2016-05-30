#pragma once

#include "Interval.h"

namespace math
{
	struct IntervalMapper
	{
		Interval from, to;

		IntervalMapper(const Interval& from, const Interval& to)
			: from(from), to(to) { }

		IntervalMapper(const IntervalMapper&) = default;

		double operator [](double) const;
	};
}