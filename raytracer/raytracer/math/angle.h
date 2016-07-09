#pragma once
#define _USE_MATH_DEFINES
#include <math.h>

namespace math
{
    class Angle final
    {
    public:
        double radians() const noexcept { return m_radians; }
        double degrees() const noexcept { return m_radians * 180 / M_PI; }

    private:
        explicit Angle(double x) noexcept
            : m_radians(x) { }
        
        friend Angle radians(long double) noexcept;
        friend Angle degrees(long double) noexcept;
        
        double m_radians;
    };

    inline Angle radians(long double x) noexcept
    {
        return Angle(x);
    }

    inline Angle degrees(long double x) noexcept
    {
        return Angle(x / 180 * M_PI);
    }

    inline Angle operator+(const Angle& x, const Angle& y) noexcept
    {
      return radians(x.radians() + y.radians()); 
    }

    inline Angle operator-(const Angle& x) noexcept
    {
      return radians(-x.radians()); 
    }

    inline Angle operator-(const Angle& x, const Angle& y) noexcept
    {
      return radians(x.radians() - y.radians()); 
    }

    inline Angle operator""_rad(long double x) noexcept
    {
        return radians(x);
    }

    inline Angle operator""_degrees(long double x) noexcept
    {
        return degrees(x);
    }

    inline Angle operator""_rad(long long unsigned x) noexcept
    {
        return radians((long double) x);
    }

    inline Angle operator""_degrees(long long unsigned x) noexcept
    {
        return degrees((long double) x);
    }

    inline Angle operator *(const Angle& angle, double factor) noexcept
    {
        return radians(angle.radians() * factor);
    }

    inline Angle operator *(double factor, const Angle& angle) noexcept
    {
        return angle * factor;
    }

    inline Angle operator /(const Angle& angle, double factor) noexcept
    {
        return radians(angle.radians() / factor);
    }

    inline bool operator <(const Angle& a, const Angle& b) noexcept
    {
        return a.radians() < b.radians();
    }

    inline bool operator >(const Angle& a, const Angle& b) noexcept
    {
        return a.radians() > b.radians();
    }

    inline bool operator <=(const Angle& a, const Angle& b) noexcept
    {
        return a.radians() <= b.radians();
    }

    inline bool operator >=(const Angle& a, const Angle& b) noexcept
    {
        return a.radians() >= b.radians();
    }

    inline bool operator ==(const Angle& a, const Angle& b) noexcept
    {
        return a.radians() == b.radians();
    }

    inline bool operator !=(const Angle& a, const Angle& b) noexcept
    {
        return a.radians() != b.radians();
    }

    inline double sin(Angle a) { return ::sin(a.radians()); }
    inline double cos(Angle a) { return ::cos(a.radians()); }
}
