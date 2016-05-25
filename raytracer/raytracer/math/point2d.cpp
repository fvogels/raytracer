#include "math/point2d.h"

using namespace math;

point2d math::operator +(const point2d& p, const vector2d& v)
{
	double x = p.x + v.x;
	double y = p.y + v.y;

	return point2d(x, y);
}

point2d math::operator +(const vector2d& v, const point2d& p)
{
	return p + v;
}

vector2d math::operator -(const point2d& p, const point2d& q)
{
	double x = p.x - q.x;
	double y = p.y - q.y;

	return vector2d(x, y);
}

double math::distance(const point2d& p, const point2d& q)
{
	return (q - p).norm();
}