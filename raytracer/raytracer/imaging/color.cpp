#include "color.h"


double clamp(double x)
{
    if (x < 0) return 0;
    else if (x > 1) return 1;
    else return x;
}

void color::clamp()
{
    r = ::clamp(r);
    g = ::clamp(g);
    b = ::clamp(b);
}

color color::clamped() const
{
    color copy = *this;
    copy.clamp();
    return copy;
}

color operator +(const color& c1, const color& c2)
{
    return color(c1.r + c2.r, c1.g + c2.g, c1.b + c2.b);
}

color operator *(const color& c, double f)
{
    return color(c.r * f, c.g * f, c.b * f);
}

color operator *(double f, const color& c)
{
    return c * f;
}

color operator /(const color& c, double f)
{
    return c * (1 / f);
}

color& operator +=(color& c1, const color& c2)
{
    return c1 = c1 + c2;
}

color& operator *=(color& c, double f)
{
    return c = c * f;
}

color& operator /=(color& c, double f)
{
    return c = c / f;
}

color& operator /=(color&, double);

