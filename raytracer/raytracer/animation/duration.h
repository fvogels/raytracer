#pragma once

namespace animation
{
    class Duration
    {
    public:
        static Duration from_milliseconds(double);
        static Duration from_seconds(double);
        static Duration zero();
        static Duration infinite();

        double milliseconds() const;
        double seconds() const;

    private:
        Duration(double);

        double m_milliseconds;
    };

    inline Duration operator""_ms(long long unsigned x) noexcept
    {
        return Duration::from_milliseconds(double(x));
    }

    inline Duration operator""_ms(long double x) noexcept
    {
        return Duration::from_milliseconds(double(x));
    }

    inline Duration operator""_s(long long unsigned x) noexcept
    {
        return Duration::from_seconds(double(x));
    }

    inline Duration operator""_s(long double x) noexcept
    {
        return Duration::from_seconds(double(x));
    }

    Duration operator +(const Duration&, const Duration&);
    Duration operator -(const Duration&);
    Duration operator -(const Duration&, const Duration&);
    Duration operator *(const Duration&, double);
    Duration operator *(double, const Duration&);
    Duration operator /(const Duration&, double);
    double operator /(const Duration&, const Duration&);

    bool operator <(const Duration&, const Duration&);
    bool operator <=(const Duration&, const Duration&);
    bool operator >=(const Duration&, const Duration&);
    bool operator >(const Duration&, const Duration&);

    bool operator ==(const Duration&, const Duration&);
    bool operator !=(const Duration&, const Duration&);
}