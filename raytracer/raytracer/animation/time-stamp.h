#pragma once

#include "animation/duration.h"


namespace animation
{
    class TimeStamp
    {
    public:
        TimeStamp();

        static TimeStamp zero() { return TimeStamp(); }
        static TimeStamp from_epoch(const Duration& duration) { return TimeStamp(duration); }

        double seconds() const;

        bool operator <(const TimeStamp&) const;
        bool operator <=(const TimeStamp&) const;
        bool operator >(const TimeStamp&) const;
        bool operator >=(const TimeStamp&) const;

        bool operator ==(const TimeStamp&) const;
        bool operator !=(const TimeStamp&) const;

    private:
        TimeStamp(const Duration&);

        Duration m_since_epoch;
    };

    inline TimeStamp operator""_S(long double x)
    {
        return TimeStamp::from_epoch(Duration::from_seconds(double(x)));
    }

    inline TimeStamp operator""_S(long long unsigned x)
    {
        return TimeStamp::from_epoch(Duration::from_seconds(double(x)));
    }

    inline TimeStamp operator""_MS(long double x)
    {
        return TimeStamp::from_epoch(Duration::from_milliseconds(double(x)));
    }

    inline TimeStamp operator""_MS(long long unsigned x)
    {
        return TimeStamp::from_epoch(Duration::from_milliseconds(double(x)));
    }

    TimeStamp operator +(const TimeStamp&, const Duration&);
    TimeStamp operator +(const Duration&, const TimeStamp&);
    TimeStamp operator -(const TimeStamp&, const Duration&);
    Duration operator -(const TimeStamp&, const TimeStamp&);

    TimeStamp& operator +=(TimeStamp&, const Duration&);

    std::ostream& operator <<(std::ostream&, const TimeStamp&);
}

namespace math
{
    template<>
    struct approximately<animation::TimeStamp>
    {
        animation::TimeStamp value;
        double delta;

        explicit approximately(const animation::TimeStamp& value, double delta = 0.00001)
            :value(value), delta(delta)
        {
            // NOP
        }

        bool close_enough(const animation::TimeStamp& other) const
        {
            return (value.seconds() - other.seconds()) < delta;
        }
    };
}