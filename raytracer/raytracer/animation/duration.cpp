#include "animation/duration.h"

using namespace animation;


Duration animation::Duration::from_milliseconds(double ms)
{
    return Duration(ms);
}

Duration animation::Duration::from_seconds(double s)
{
    return Duration(s * 1000.0);
}

animation::Duration::Duration(double ms)
    : m_milliseconds(ms)
{
    // NOP
}

double animation::Duration::milliseconds() const
{
    return m_milliseconds;
}

Duration animation::operator +(const Duration& d1, const Duration& d2)
{
    return Duration::from_milliseconds(d1.milliseconds() + d2.milliseconds());
}

Duration animation::operator -(const Duration& d1, const Duration& d2)
{
    return Duration::from_milliseconds(d1.milliseconds() - d2.milliseconds());
}

Duration animation::operator *(const Duration& duration, double factor)
{
    return Duration::from_milliseconds(duration.milliseconds() * factor);
}

Duration animation::operator *(double factor, const Duration& duration)
{
    return duration * factor;
}

Duration animation::operator /(const Duration& duration, double factor)
{
    return duration * (1.0 / factor);
}

bool animation::operator <(const Duration& d1, const Duration& d2)
{
    return d1.milliseconds() < d2.milliseconds();
}

bool animation::operator <=(const Duration& d1, const Duration& d2)
{
    return d1.milliseconds() <= d2.milliseconds();
}

bool animation::operator >=(const Duration& d1, const Duration& d2)
{
    return d1.milliseconds() >= d2.milliseconds();
}

bool animation::operator >(const Duration& d1, const Duration& d2)
{
    return d1.milliseconds() >= d2.milliseconds();
}

bool animation::operator ==(const Duration& d1, const Duration& d2)
{
    return d1.milliseconds() == d2.milliseconds();
}

bool animation::operator !=(const Duration& d1, const Duration& d2)
{
    return d1.milliseconds() != d2.milliseconds();
}