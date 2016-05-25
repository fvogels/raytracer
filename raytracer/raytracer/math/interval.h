#pragma once

namespace math
{
	struct interval
	{
		double lower, upper;

		interval(double lower, double upper)
			: lower(lower), upper(upper) { }

		interval(const interval&) = default;

		double size() const;
		bool contains(double x) const;

		double to_relative(double x) const;
		double from_relative(double t) const;
	};
}