#pragma once

#include "Interval.h"

namespace math
{
	struct Interval_mapper
	{
		Interval from, to;

		Interval_mapper(const Interval& from, const Interval& to)
			: from(from), to(to) { }

		Interval_mapper(const Interval_mapper&) = default;

		double operator [](double) const;
	};
}