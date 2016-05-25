#pragma once

#include "interval.h"

namespace math
{
	struct interval_mapper
	{
		interval from, to;

		interval_mapper(const interval& from, const interval& to)
			: from(from), to(to) { }

		interval_mapper(const interval_mapper&) = default;

		double operator [](double) const;
	};
}