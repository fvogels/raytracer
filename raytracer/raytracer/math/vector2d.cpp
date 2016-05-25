#include "math/vector2d.h"

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