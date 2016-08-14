#define _USE_MATH_DEFINES
#include "math/angle.h"
#include <math.h>


using namespace math;


math::Angle::Angle()
    : Angle(0) { }

math::Angle::Angle(double x)
    : m_radians(x) 
{ 
    // NOP
}

double math::Angle::radians() const 
{
    return m_radians; 
}

double math::Angle::degrees() const
{
    return m_radians * 180 / M_PI; 
}

Angle math::Angle::degrees(long double x)
{
    return Angle(double(x) / 180 * M_PI); 
}

Angle math::Angle::radians(long double x)
{
    return Angle(double(x)); 
}

Angle math::operator+(const Angle& x, const Angle& y)
{
    return Angle::radians(x.radians() + y.radians());
}

Angle math::operator-(const Angle& x)
{
    return Angle::radians(-x.radians());
}

Angle math::operator-(const Angle& x, const Angle& y)
{
    return Angle::radians(x.radians() - y.radians());
}

Angle math::operator *(const Angle& angle, double factor)
{
    return Angle::radians(angle.radians() * factor);
}

Angle math::operator *(double factor, const Angle& angle)
{
    return angle * factor;
}

Angle math::operator /(const Angle& angle, double factor)
{
    return Angle::radians(angle.radians() / factor);
}

Angle& math::operator +=(Angle& x, const Angle& y)
{
    return (x = x + y);
}

Angle& math::operator -=(Angle& x, const Angle& y)
{
    return (x = x - y);
}

Angle& math::operator *=(Angle& x, double f)
{
    return (x = x * f);
}

Angle& math::operator /=(Angle& x, double f)
{
    return (x = x / f);
}

Angle math::operator""_rad(long double x)
{
    return Angle::radians(x);
}

Angle math::operator""_degrees(long double x)
{
    return Angle::degrees(x);
}

Angle math::operator""_rad(long long unsigned x)
{
    return Angle::radians((long double)x);
}

Angle math::operator""_degrees(long long unsigned x)
{
    return Angle::degrees((long double)x);
}

bool math::operator <(const Angle& a, const Angle& b)
{
    return a.radians() < b.radians();
}

bool math::operator >(const Angle& a, const Angle& b)
{
    return a.radians() > b.radians();
}

bool math::operator <=(const Angle& a, const Angle& b)
{
    return a.radians() <= b.radians();
}

bool math::operator >=(const Angle& a, const Angle& b)
{
    return a.radians() >= b.radians();
}

bool math::operator ==(const Angle& a, const Angle& b)
{
    return a.radians() == b.radians();
}

bool math::operator !=(const Angle& a, const Angle& b)
{
    return a.radians() != b.radians();
}