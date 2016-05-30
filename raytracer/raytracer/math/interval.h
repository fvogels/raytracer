#pragma once

namespace math
{
	struct Interval
	{
		double lower, upper;

		Interval(double lower, double upper)
			: lower(lower), upper(upper) { }

		Interval(const Interval&) = default;

		double size() const;
		bool contains(double x) const;

		double to_relative(double x) const;
		double from_relative(double t) const;
	};
}