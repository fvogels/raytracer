#include "math/vector2d.h"
#include "math/util.h"
#include <math.h>

using namespace math;


std::ostream& math::operator <<(std::ostream& out, const Vector2D& v)
{
	return out << "(" << v.x << "," << v.y << ")";
}

constexpr double math::Vector2D::dot(const Vector2D& v) const noexcept
{
	return x * v.x + y * v.y;
}

constexpr double math::Vector2D::norm_sqr() const noexcept
{
	return dot(*this);
}

double math::Vector2D::norm() const noexcept
{
	return std::sqrt(norm_sqr());
}

void math::Vector2D::normalize() noexcept
{
	*this = normalized();
}

Vector2D math::Vector2D::normalized() const noexcept
{
	return *this / norm();
}

Vector2D& math::Vector2D::operator+=(const Vector2D& v) noexcept
{
	return *this = *this + v;
}

Vector2D& math::Vector2D::operator-=(const Vector2D& v) noexcept
{
	return *this = *this - v;
}

Vector2D& math::Vector2D::operator*=(double factor) noexcept
{
	return *this = *this * factor;
}

Vector2D& math::Vector2D::operator/=(double factor) noexcept
{
	return *this = *this / factor;
}

bool math::Vector2D::is_unit() const noexcept
{
	return norm() == approx(1);
}

constexpr bool math::Vector2D::is_perpendicular_on(const Vector2D& v) const noexcept
{
	return dot(v) == approx(0);
}
