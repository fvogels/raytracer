#pragma once

#include <limits>
#include <algorithm>


namespace math
{
    template<typename T>
    struct Interval
    {
        T lower, upper;

        Interval(T lower, T upper)
            : lower(lower), upper(upper) { }

        Interval(const Interval&) = default;

        static Interval empty()
        {
            return Interval(std::numeric_limits<T>::infinity(), -std::numeric_limits<T>::infinity());
        }

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

        Interval merge(const Interval& other) const
        {
            return Interval(std::min(lower, other.lower), std::max(upper, other.upper));
        }
    };
}