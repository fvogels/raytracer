#include "math/point2D.h"
#include "math/util.h"

using namespace math;

Point2D math::operator +(const Point2D& p, const Vector2D& v)
{
	double x = p.x + v.x;
	double y = p.y + v.y;

	return Point2D(x, y);
}

Point2D math::operator +(const Vector2D& v, const Point2D& p)
{
	return p + v;
}

Vector2D math::operator -(const Point2D& p, const Point2D& q)
{
	double x = p.x - q.x;
	double y = p.y - q.y;

	return Vector2D(x, y);
}

Point2D math::operator -(const Point2D& p, const Vector2D& v)
{
	double x = p.x - v.x;
	double y = p.y - v.y;

	return Point2D(x, y);
}

double math::distance(const Point2D& p, const Point2D& q)
{
	return (q - p).norm();
}

bool math::operator ==(const Point2D& p, const Point2D& q)
{
	return p.x == approx(q.x) && p.y == approx(q.y);
}

bool math::operator !=(const Point2D& p, const Point2D& q)
{
	return !(p == q);
}