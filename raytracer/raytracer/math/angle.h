#pragma once
#include "math/approx.h"
#include <iostream>


namespace math
{
    /// <summary>
    /// Represents an angle. Used to be able to distinguish angles from other double values.
    /// Also ensures that no mistakes are made w.r.t. degrees vs radians.
    /// </summary>
    class Angle final
    {
    public:
        Angle();

        double radians() const;
        double degrees() const;

        static Angle degrees(long double);
        static Angle radians(long double);

    private:
        explicit Angle(double);
        
        double m_radians;
    };

    Angle operator+(const Angle& x, const Angle& y);
    Angle operator-(const Angle& x);
    Angle operator-(const Angle& x, const Angle& y);
    Angle operator *(const Angle& angle, double factor);
    Angle operator *(double factor, const Angle& angle);
    Angle operator /(const Angle& angle, double factor);

    Angle& operator +=(Angle& x, const Angle& y);
    Angle& operator -=(Angle& x, const Angle& y);
    Angle& operator *=(Angle& x, double f);
    Angle& operator /=(Angle& x, double f);

    Angle operator""_rad(long double x);
    Angle operator""_degrees(long double x);
    Angle operator""_rad(long long unsigned x);
    Angle operator""_degrees(long long unsigned x);

    bool operator <(const Angle& a, const Angle& b);
    bool operator >(const Angle& a, const Angle& b);
    bool operator <=(const Angle& a, const Angle& b);
    bool operator >=(const Angle& a, const Angle& b);
    bool operator ==(const Angle& a, const Angle& b);
    bool operator !=(const Angle& a, const Angle& b);

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
        return out << angle.degrees() << "deg";
    }
}
