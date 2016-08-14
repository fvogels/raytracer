#pragma once

#include "math/approx.h"
#include <iostream>

namespace imaging
{
    struct Color final
    {
        double r, g, b;

        constexpr Color() : Color(0, 0, 0) { }

        constexpr Color(double r, double g, double b)
            : r(r), g(g), b(b) { }

        void clamp();
        Color clamped() const;

        void quantize(unsigned);
        Color quantized(unsigned) const;

        void invert();
        Color inverted() const;
    };

    Color operator +(const Color&, const Color&);
    Color operator -(const Color&, const Color&);
    Color operator *(const Color&, double);
    Color operator *(double, const Color&);
    Color operator *(const Color&, const Color&);
    Color operator /(const Color&, double);

    Color& operator +=(Color&, const Color&);
    Color& operator -=(Color&, const Color&);
    Color& operator *=(Color&, double);
    Color& operator /=(Color&, double);

    bool operator ==(const Color&, const Color&);
    bool operator !=(const Color&, const Color&);

    std::ostream& operator <<(std::ostream&, const Color&);

    // Example usage: Color c = colors::black();
    namespace colors
    {
        constexpr Color black()   { return Color{ 0, 0, 0 }; }
        constexpr Color white()   { return Color{ 1, 1, 1 }; }
        constexpr Color red()     { return Color{ 1, 0, 0 }; }
        constexpr Color green()   { return Color{ 0, 1, 0 }; }
        constexpr Color blue()    { return Color{ 0, 0, 1 }; }
        constexpr Color yellow()  { return Color{ 1, 1, 0 }; }
        constexpr Color magenta() { return Color{ 1, 0, 1 }; }
        constexpr Color cyan()    { return Color{ 0, 1, 1 }; }
    }
}

namespace math
{
    template<>
    struct approximately<imaging::Color>
    {
        imaging::Color value;
        double delta;

        explicit approximately(const imaging::Color& value, double delta = 0.00001)
            :value(value), delta(delta)
        {
            // NOP
        }

        bool close_enough(const imaging::Color& other) const
        {
            return
                value.r == approx(other.r) &&
                value.g == approx(other.g) &&
                value.b == approx(other.b);
        }
    };
}