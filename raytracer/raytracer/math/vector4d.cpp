#include "math/vector4d.h"
#include <math.h>

using namespace math;


std::ostream& math::operator <<(std::ostream& out, const Vector4D& v)
{
    return out << "(" << v.x << "," << v.y << "," << v.z << "," << v.w << ")";
}

double math::Vector4D::dot(const Vector4D& v) const noexcept
{
    return x * v.x + y * v.y + z * v.z + w * v.w;
}

double math::Vector4D::norm_sqr() const noexcept
{
    return dot(*this);
}

double math::Vector4D::norm() const noexcept
{
    return sqrt(norm_sqr());
}

void math::Vector4D::normalize() noexcept
{
    *this = normalized();
}

Vector4D math::Vector4D::normalized() const noexcept
{
    return *this / norm();
}

Vector4D& math::Vector4D::operator+=(const Vector4D& v) noexcept
{
    return *this = *this + v;
}

Vector4D& math::Vector4D::operator-=(const Vector4D& v) noexcept
{
    return *this = *this - v;
}

Vector4D& math::Vector4D::operator*=(double factor) noexcept
{
    return *this = *this * factor;
}

Vector4D& math::Vector4D::operator/=(double factor) noexcept
{
    return *this = *this / factor;
}

bool math::Vector4D::is_unit() const noexcept
{
    return norm() == approx(1.0);
}

Vector4D math::operator +(const Vector4D& u, const Vector4D& v) noexcept
{
    return Vector4D(u.x + v.x, u.y + v.y, u.z + v.z, u.w + v.w);
}

Vector4D math::operator -(const Vector4D& v) noexcept
{
    return Vector4D(-v.x, -v.y, -v.z, -v.w);
}

Vector4D math::operator -(const Vector4D& u, const Vector4D& v) noexcept
{
    return Vector4D(u.x - v.x, u.y - v.y, u.z - v.z, u.w - v.w);
}

Vector4D math::operator *(const Vector4D& v, double factor) noexcept
{
    return Vector4D(v.x * factor, v.y * factor, v.z * factor, v.w * factor);
}

Vector4D math::operator *(double factor, const Vector4D& v) noexcept
{
    return v * factor;
}

Vector4D math::operator /(const Vector4D& v, double factor) noexcept
{
    return v * (1.0 / factor);
}

bool math::operator ==(const Vector4D& u, const Vector4D& v) noexcept
{
    return u.x == v.x && u.y == v.y && u.z == v.z && u.w == v.w;
}

bool math::operator !=(const Vector4D& u, const Vector4D& v) noexcept
{
    return !(u == v);
}
