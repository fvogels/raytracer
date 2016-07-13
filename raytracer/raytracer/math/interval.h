#pragma once

#include <limits>
#include <algorithm>


namespace math
{
    template<typename T>
    struct Interval
    {
        T lower, upper;

        // TODO Make private and make use of factory methods
        constexpr Interval(T lower, T upper)
            : lower(lower), upper(upper) { }

        Interval(const Interval&) = default;

        static constexpr Interval empty()
        {
            return Interval(std::numeric_limits<T>::infinity(), -std::numeric_limits<T>::infinity());
        }

        static constexpr Interval infinite()
        {
            return Interval(-std::numeric_limits<T>::infinity(), std::numeric_limits<T>::infinity());
        }

        // Bounds are taken as is. If x > y, then interval is empty.
        static constexpr Interval from_raw_bounds(double x, double y)
        {
            return Interval(x, y);
        }

        // Bounds are "sorted" so that interval is not empty
        static constexpr Interval from_bounds(double x, double y)
        {
            return Interval(std::min(x, y), std::max(x, y));
        }

        constexpr decltype(upper-lower) size() const
        {
            return upper - lower;
        }

        constexpr bool contains(T x) const
        {
            return lower <= x && x <= upper;
        }

        constexpr double to_relative(T x) const
        {
            return (x - lower) / size();
        }

        constexpr T from_relative(double t) const
        {
            return t * size() + lower;
        }

        Interval<T> merge(const Interval& other) const
        {
            return Interval(std::min(lower, other.lower), std::max(upper, other.upper));
        }

        Interval<T> intersect(const Interval& other) const
        {
            return Interval(std::max(lower, other.lower), std::min(upper, other.upper));
        }

        template<unsigned I>
        constexpr T bound() const
        {
            static_assert(I == 0 || I == 1, "I must be either 0 or 1");

            return I == 0 ? this->lower : this->upper;
        }
    };
}