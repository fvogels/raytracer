#include "math/point2d.h"


using namespace math;


double math::distance(const Point2D& p, const Point2D& q) noexcept
{
	return (q - p).norm();
}

std::ostream& math::operator <<(std::ostream& out, const Point2D& p)
{
	return out << "(" << p.x << "," << p.y << ")";
}