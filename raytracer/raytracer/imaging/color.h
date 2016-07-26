#pragma once

#include "math/approx.h"
#include <iostream>

namespace imaging
{
    struct Color final
    {
        double r, g, b;

        constexpr Color() noexcept : Color(0, 0, 0) { }

        constexpr Color(double r, double g, double b) noexcept
            : r(r), g(g), b(b) { }

        void clamp() noexcept;
        Color clamped() const noexcept;

        void quantize(unsigned) noexcept;
        Color quantized(unsigned) const noexcept;

        void invert() noexcept;
        Color inverted() const noexcept;
    };

    Color operator +(const Color&, const Color&) noexcept;
    Color operator -(const Color&, const Color&) noexcept;
    Color operator *(const Color&, double) noexcept;
    Color operator *(double, const Color&) noexcept;
    Color operator *(const Color&, const Color&) noexcept;
    Color operator /(const Color&, double) noexcept;

    Color& operator +=(Color&, const Color&) noexcept;
    Color& operator -=(Color&, const Color&) noexcept;
    Color& operator *=(Color&, double) noexcept;
    Color& operator /=(Color&, double) noexcept;

    bool operator ==(const Color&, const Color&) noexcept;
    bool operator !=(const Color&, const Color&) noexcept;

    std::ostream& operator <<(std::ostream&, const Color&);

    // Example usage: Color c = colors::black();
    namespace colors
    {
        constexpr Color black()   noexcept { return Color{ 0, 0, 0 }; }
        constexpr Color white()   noexcept { return Color{ 1, 1, 1 }; }
        constexpr Color red()     noexcept { return Color{ 1, 0, 0 }; }
        constexpr Color green()   noexcept { return Color{ 0, 1, 0 }; }
        constexpr Color blue()    noexcept { return Color{ 0, 0, 1 }; }
        constexpr Color yellow()  noexcept { return Color{ 1, 1, 0 }; }
        constexpr Color magenta() noexcept { return Color{ 1, 0, 1 }; }
        constexpr Color cyan()    noexcept { return Color{ 0, 1, 1 }; }
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