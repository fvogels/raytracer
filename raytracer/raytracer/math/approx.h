#pragma once

#include <math.h>
#include <iostream>

namespace math
{
    template<typename>
    struct approx;

    template<>
    struct approx<double>
    {
        double value;
        double delta;

        explicit approx(double value, double delta = 0.00001) noexcept
            : value(value), delta(delta) { }

        bool close_enough(double other) const
        {
            return std::abs(other - value) < delta;
        }
    };

    template<typename T>
    bool operator ==(const approx<T>& x, T y) noexcept
    {
        return x.close_enough(y);
    }

    template<typename T>
    bool operator ==(T x, const approx<T>& y) noexcept
    {
        return y == x;
    }

    template<typename T>
    bool operator !=(const approx<T>& x, T y) noexcept
    {
        return !(x == y);
    }

    template<typename T>
    bool operator !=(double x, const approx<T>& y) noexcept
    {
        return !(x == y);
    }

    template<typename T>
    std::ostream& operator <<(std::ostream& out, const approx<T>& x)
    {
        return out << "approx(" << x.value << ")";
    }
}