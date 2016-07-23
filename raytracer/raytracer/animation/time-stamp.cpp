#include "animation/time-stamp.h"

using namespace animation;


animation::TimeStamp::TimeStamp()
    : m_since_epoch(Duration::zero())
{
    // NOP
}

animation::TimeStamp::TimeStamp(const Duration& since_epoch)
    : m_since_epoch(since_epoch)
{
    // NOP
}

double animation::TimeStamp::seconds() const
{
    return m_since_epoch.seconds();
}

TimeStamp animation::operator +(const TimeStamp& ts, const Duration& d)
{
    return TimeStamp(ts.m_since_epoch + d);
}

TimeStamp animation::operator +(const Duration& d, const TimeStamp& ts)
{
    return ts + d;
}

TimeStamp animation::operator -(const TimeStamp& ts, const Duration& d)
{
    return ts + -d;
}

Duration animation::operator -(const TimeStamp& ts1, const TimeStamp& ts2)
{
    return ts1.m_since_epoch - ts2.m_since_epoch;
}

bool animation::TimeStamp::operator <(const TimeStamp& ts) const
{
    return m_since_epoch < ts.m_since_epoch;
}

bool animation::TimeStamp::operator >(const TimeStamp& ts) const
{
    return m_since_epoch < ts.m_since_epoch;
}

bool animation::TimeStamp::operator <=(const TimeStamp& ts) const
{
    return m_since_epoch < ts.m_since_epoch;
}

bool animation::TimeStamp::operator >=(const TimeStamp& ts) const
{
    return m_since_epoch < ts.m_since_epoch;
}

TimeStamp& animation::operator +=(TimeStamp& ts, const Duration& duration)
{
    return (ts = ts + duration);
}

bool animation::TimeStamp::operator ==(const TimeStamp& ts) const
{
    return m_since_epoch == ts.m_since_epoch;
}

bool animation::TimeStamp::operator !=(const TimeStamp& ts) const
{
    return !(*this == ts);
}