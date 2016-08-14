#pragma once

#include <limits>
#include <algorithm>
#include <iostream>


namespace math
{
    template<typename T>
    struct Interval
    {
        T lower, upper;

        constexpr Interval(T lower, T upper)
            : lower(lower), upper(upper) { }

        Interval(const Interval<T>&) = default;

        static constexpr Interval<T> empty()
        {
            return Interval<T>(std::numeric_limits<T>::infinity(), -std::numeric_limits<T>::infinity());
        }

        static constexpr Interval<T> infinite()
        {
            return Interval<T>(-std::numeric_limits<T>::infinity(), std::numeric_limits<T>::infinity());
        }

        // Bounds are taken as is. If x > y, then interval is empty.
        static constexpr Interval<T> from_raw_bounds(double x, double y)
        {
            return Interval(x, y);
        }

        // Bounds are "sorted" so that interval is not empty
        static constexpr Interval<T> from_bounds(double x, double y)
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

        T center() const noexcept
        {
            return lower + size() / 2;
        }

        bool is_infinite() const noexcept
        {
            return lower == -std::numeric_limits<T>::infinity() || upper == std::numeric_limits<T>::infinity();
        }
    };

    template<typename T>
    std::ostream& operator <<(std::ostream& out, const Interval<T>& interval)
    {
        return out << "[" << interval.lower << ", " << interval.upper << "]";
    }

    /// <summary>
    /// Factory function for intervals. Easier to use than the constructor
    /// as it is not necessary to specify the type T. If <paramref name="lower" /> is greater than
    /// <paramref name="upper" />, the interval will be considered empty.
    /// </summary>
    /// <example>
    /// <code>
    /// // Creates the object Interval&lt;double&gt;(0, 5)
    /// auto range = interval(0.0, 5.0);
    /// </code>
    /// </example>
    template<typename T>
    constexpr Interval<T> interval(const T& lower, const T& upper)
    {
        static_assert(!std::is_same<T, int>::value, "fkl");

        return Interval<T>(lower, upper);
    }    

    /// <summary>
    /// Factory function for intervals. Easier to use than the constructor
    /// as it is not necessary to specify the type T. If <paramref name="lower" /> is greater than
    /// <paramref name="upper" />, the bounds will be switched around so as to make the interval nonempty.
    /// </summary>
    /// <example>
    /// <code>
    /// // Switches bounds resulting in Interval&lt;double&gt;(5, 7)
    /// auto range = nonempty_interval(7.0, 5.0);
    /// </code>
    /// </example>
    template<typename T>
    constexpr Interval<T> nonempty_interval(const T& lower, const T& upper)
    {
        return lower <= upper ? interval(lower, upper) : interval(upper, lower);
    }
}
