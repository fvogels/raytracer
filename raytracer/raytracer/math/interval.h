#pragma once

namespace math
{
    template<typename T>
    struct Interval
    {
        T lower, upper;

        Interval(T lower, T upper)
            : lower(lower), upper(upper) { }

        Interval(const Interval&) = default;

        T size() const
        {
            return upper - lower;
        }

        bool contains(T x) const
        {
            return lower <= x && x <= upper;
        }

        double to_relative(T x) const
        {
            return (x - lower) / size();
        }

        T from_relative(double t) const
        {
            return t * size() + lower;
        }
    };
}