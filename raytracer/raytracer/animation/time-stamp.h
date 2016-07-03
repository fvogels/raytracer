#pragma once

#include "animation/duration.h"


namespace animation
{
    class TimeStamp
    {
    public:
        TimeStamp();

        double seconds() const;

    private:
        TimeStamp(const Duration&);

        Duration m_since_epoch;

        friend TimeStamp operator +(const TimeStamp&, const Duration&);
        friend TimeStamp operator +(const Duration&, const TimeStamp&);
        friend TimeStamp operator -(const TimeStamp&, const Duration&);
        friend Duration operator -(const TimeStamp&, const TimeStamp&);
    };
}