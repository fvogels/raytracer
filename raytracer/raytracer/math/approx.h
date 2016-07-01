#pragma once

#include <math.h>
#include <iostream>

namespace math
{
    template<typename>
    struct approximately;

    template<>
    struct approximately<double>
    {
        double value;
        double delta;

        explicit approximately(double value, double delta = 0.00001) noexcept
            : value(value), delta(delta) { }

        bool close_enough(double other) const
        {
            return fabs(other - value) < delta;
        }
    };

    template<typename T>
    approximately<T> approx(T x)
    {
        return approximately<T>(x);
    }

    template<typename T>
    bool operator ==(const approximately<T>& x, T y) noexcept
    {
        return x.close_enough(y);
    }

    template<typename T>
    bool operator ==(T x, const approximately<T>& y) noexcept
    {
        return y == x;
    }

    template<typename T>
    bool operator !=(const approximately<T>& x, T y) noexcept
    {
        return !(x == y);
    }

    template<typename T>
    bool operator !=(double x, const approximately<T>& y) noexcept
    {
        return !(x == y);
    }

    template<typename T>
    std::ostream& operator <<(std::ostream& out, const approximately<T>& x)
    {
        return out << "approximately(" << x.value << ")";
    }
}
