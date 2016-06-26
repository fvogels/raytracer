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

Point2D math::operator +(const Point2D& p, const Vector2D& v) noexcept
{
    return Point2D(p.x + v.x, p.y + v.y);
}

Point2D math::operator +(const Vector2D& v, const Point2D& p) noexcept
{
    return p + v;
}

Vector2D math::operator -(const Point2D& p, const Point2D& q) noexcept
{
    return Vector2D(p.x - q.x, p.y - q.y);
}

Point2D math::operator -(const Point2D& p, const Vector2D& v) noexcept
{
    return Point2D(p.x - v.x, p.y - v.y);
}

bool math::operator ==(const Point2D& p, const Point2D& q) noexcept
{
    return p.x == approx<double>(q.x) && p.y == approx<double>(q.y);
}

bool math::operator !=(const Point2D& p, const Point2D& q) noexcept
{
    return !(p == q);
}