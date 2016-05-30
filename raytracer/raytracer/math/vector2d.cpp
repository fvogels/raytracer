#include "math/vector2d.h"
#include "math/util.h"
#include <math.h>

using namespace math;

Vector2D math::operator +(const Vector2D& u, const Vector2D& v)
{
	double x = u.x + v.x;
	double y = u.y + v.y;

	return Vector2D(x, y);
}

Vector2D math::operator -(const Vector2D& v)
{
	double x = -v.x;
	double y = -v.y;

	return Vector2D(x, y);
}


Vector2D math::operator -(const Vector2D& u, const Vector2D& v)
{
	double x = u.x - v.x;
	double y = u.y - v.y;

	return Vector2D(x, y);
}

Vector2D math::operator *(const Vector2D& v, double factor)
{
	double x = v.x * factor;
	double y = v.y * factor;

	return Vector2D(x, y);
}

Vector2D math::operator *(double factor, const Vector2D& v)
{
	return v * factor;
}

Vector2D math::operator /(const Vector2D& v, double factor)
{
	return v * (1.0 / factor);
}

std::ostream& math::operator <<(std::ostream& out, const Vector2D& v)
{
	return out << "(" << v.x << "," << v.y << ")";
}

double math::Vector2D::dot(const Vector2D& v) const
{
	double result = 0;

	result += x * v.x;
	result += y * v.y;

	return result;
}

double math::Vector2D::norm_sqr() const
{
	return dot(*this);
}

double math::Vector2D::norm() const
{
	return std::sqrt(norm_sqr());
}

void math::Vector2D::normalize()
{
	*this = normalized();
}

Vector2D math::Vector2D::normalized() const
{
	return *this / norm();
}

Vector2D& math::Vector2D::operator+=(const Vector2D& v)
{
	return *this = *this + v;
}

Vector2D& math::Vector2D::operator-=(const Vector2D& v)
{
	return *this = *this - v;
}

Vector2D& math::Vector2D::operator*=(double factor)
{
	return *this = *this * factor;
}

Vector2D& math::Vector2D::operator/=(double factor)
{
	return *this = *this / factor;
}

bool math::Vector2D::is_unit() const
{
	return norm() == approx(1);
}

bool math::Vector2D::is_perpendicular_on(const Vector2D& v) const
{
	return dot(v) == approx(0);
}

bool math::operator ==(const Vector2D& u, const Vector2D& v)
{
	return u.x == approx(v.x) && u.y == approx(v.y);
}

bool math::operator !=(const Vector2D& u, const Vector2D& v)
{
	return !(u == v);
}