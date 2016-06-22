#include "math/functions/patterns.h"

using namespace math;


Function<bool, const Point2D&> math::functions::checkered()
{
	std::function<bool(const Point2D&)> function = [](const Point2D& p)
	{
		double x = p.x - std::floor(p.x);
		double y = p.y - std::floor(p.y);

		return (x < 0.5) != (y < 0.5);
	};

	return from_lambda<bool, const Point2D&>(function);
}

Function<bool, const Point2D&> math::functions::horizontal_lines(double thickness)
{
	std::function<bool(const Point2D&)> function = [thickness](const Point2D& p)
	{
		auto y = p.y * 10;

		return std::abs(y - std::round(y)) < thickness / 2;
	};

	return from_lambda<bool, const Point2D&>(function);
}

Function<bool, const Point2D&> math::functions::vertical_lines(double thickness)
{
	std::function<bool(const Point2D&)> function = [thickness](const Point2D& p)
	{
		auto x = p.x * 10;

		return std::abs(x - std::round(x)) < thickness / 2;
	};

	return from_lambda<bool, const Point2D&>(function);
}