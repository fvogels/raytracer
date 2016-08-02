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

    TimeStamp operator +(const TimeStamp&, const Duration&);
    TimeStamp operator +(const Duration&, const TimeStamp&);
    TimeStamp operator -(const TimeStamp&, const Duration&);
    Duration operator -(const TimeStamp&, const TimeStamp&);

    TimeStamp& operator +=(TimeStamp&, const Duration&);
}
