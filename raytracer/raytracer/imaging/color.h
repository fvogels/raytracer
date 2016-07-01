#pragma once

#include "math/approx.h"
#include <iostream>

namespace imaging
{
    struct color final
    {
        double r, g, b;

        constexpr color() : color(0, 0, 0) { }

        constexpr color(double r, double g, double b)
            : r(r), g(g), b(b) { }

        void clamp();
        color clamped() const;
    };

    color operator +(const color&, const color&);
    color operator *(const color&, double);
    color operator *(double, const color&);
    color operator *(const color&, const color&);
    color operator /(const color&, double);

    color& operator +=(color&, const color&);
    color& operator *=(color&, double);
    color& operator /=(color&, double);

    bool operator ==(const color&, const color&);
    bool operator !=(const color&, const color&);

    std::ostream& operator <<(std::ostream&, const color&);

    // Example usage: color c = colors::black();
    namespace colors
    {
        constexpr color black()   { return color{ 0, 0, 0 }; }
        constexpr color white()   { return color{ 1, 1, 1 }; }
        constexpr color red()     { return color{ 1, 0, 0 }; }
        constexpr color green()   { return color{ 0, 1, 0 }; }
        constexpr color blue()    { return color{ 0, 0, 1 }; }
        constexpr color yellow()  { return color{ 1, 1, 0 }; }
        constexpr color magenta() { return color{ 1, 0, 1 }; }
        constexpr color cyan()    { return color{ 0, 1, 1 }; }
    }
}

namespace math
{
    template<>
    struct approximately<imaging::color>
    {
        imaging::color value;
        double delta;

        explicit approximately(const imaging::color& value, double delta = 0.00001)
            :value(value), delta(delta)
        {
            // NOP
        }

        bool close_enough(const imaging::color& other) const
        {
            return
                value.r == approx(other.r) &&
                value.g == approx(other.g) &&
                value.b == approx(other.b);
        }
    };
}