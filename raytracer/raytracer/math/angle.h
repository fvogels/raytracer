#pragma once
#define _USE_MATH_DEFINES
#include "math/approx.h"
#include <math.h>
#include <iostream>


namespace math
{
    class Angle final
    {
    public:
        double radians() const noexcept { return m_radians; }
        double degrees() const noexcept { return m_radians * 180 / M_PI; }

        static Angle degrees(long double x) noexcept { return Angle(x / 180 * M_PI); }
        static Angle radians(long double x) noexcept { return Angle(x); }

    private:
        explicit Angle(double x) noexcept
            : m_radians(x) { }
        
        double m_radians;
    };

    inline Angle operator+(const Angle& x, const Angle& y) noexcept
    {
      return Angle::radians(x.radians() + y.radians()); 
    }

    inline Angle operator-(const Angle& x) noexcept
    {
      return Angle::radians(-x.radians()); 
    }

    inline Angle operator-(const Angle& x, const Angle& y) noexcept
    {
      return Angle::radians(x.radians() - y.radians()); 
    }

    inline Angle operator *(const Angle& angle, double factor) noexcept
    {
        return Angle::radians(angle.radians() * factor);
    }

    inline Angle operator *(double factor, const Angle& angle) noexcept
    {
        return angle * factor;
    }

    inline Angle operator /(const Angle& angle, double factor) noexcept
    {
        return Angle::radians(angle.radians() / factor);
    }

    inline Angle& operator +=(Angle& x, const Angle& y) noexcept
    {
        return (x = x + y);
    }

    inline Angle& operator -=(Angle& x, const Angle& y) noexcept
    {
        return (x = x - y);
    }

    inline Angle& operator *=(Angle& x, double f) noexcept
    {
        return (x = x * f);
    }

    inline Angle& operator /=(Angle& x, double f) noexcept
    {
        return (x = x / f);
    }

    inline Angle operator""_rad(long double x) noexcept
    {
        return Angle::radians(x);
    }

    inline Angle operator""_degrees(long double x) noexcept
    {
        return Angle::degrees(x);
    }

    inline Angle operator""_rad(long long unsigned x) noexcept
    {
        return Angle::radians((long double) x);
    }

    inline Angle operator""_degrees(long long unsigned x) noexcept
    {
        return Angle::degrees((long double) x);
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

    template<>
    struct approximately<Angle>
    {
        Angle value;
        double delta;

        explicit approximately(const Angle& value, double delta = 0.00001)
            :value(value), delta(delta)
        {
            // NOP
        }

        bool close_enough(const Angle& other) const
        {
            return (value.radians() - other.radians()) < delta;
        }
    };

    inline std::ostream& operator <<(std::ostream& out, Angle angle)
    {
        return out << angle.degrees() << "°";
    }
}
