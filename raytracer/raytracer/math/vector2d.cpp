#include "math/vector2d.h"
#include "math/util.h"
#include <math.h>

using namespace math;

vector2d math::operator +(const vector2d& u, const vector2d& v)
{
	double x = u.x + v.x;
	double y = u.y + v.y;

	return vector2d(x, y);
}

vector2d math::operator -(const vector2d& u, const vector2d& v)
{
	double x = u.x - v.x;
	double y = u.y - v.y;

	return vector2d(x, y);
}

vector2d math::operator *(const vector2d& v, double factor)
{
	double x = v.x * factor;
	double y = v.y * factor;

	return vector2d(x, y);
}

vector2d math::operator *(double factor, const vector2d& v)
{
	return v * factor;
}

vector2d math::operator /(const vector2d& v, double factor)
{
	return v * (1.0 / factor);
}

std::ostream& math::operator <<(std::ostream& out, const vector2d& v)
{
	return out << "(" << v.x << "," << v.y << ")";
}

double math::vector2d::dot(const vector2d& v) const
{
	double result = 0;

	result += x * v.x;
	result += y * v.y;

	return result;
}

double math::vector2d::norm_sqr() const
{
	return dot(*this);
}

double math::vector2d::norm() const
{
	return std::sqrt(norm_sqr());
}

void math::vector2d::normalize()
{
	*this = normalized();
}

vector2d math::vector2d::normalized() const
{
	return *this / norm();
}

vector2d& math::vector2d::operator+=(const vector2d& v)
{
	return *this = *this + v;
}

vector2d& math::vector2d::operator-=(const vector2d& v)
{
	return *this = *this - v;
}

vector2d& math::vector2d::operator*=(double factor)
{
	return *this = *this * factor;
}

vector2d& math::vector2d::operator/=(double factor)
{
	return *this = *this / factor;
}

bool math::vector2d::is_unit() const
{
	return norm() == approx(1);
}

bool math::vector2d::is_perpendicular_on(const vector2d& v) const
{
	return dot(v) == approx(0);
}