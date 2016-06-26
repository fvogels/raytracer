#include "imaging/color.h"
#include "math/util.h"

using namespace imaging;


double clamp(double x)
{
    if (x < 0) return 0;
    else if (x > 1) return 1;
    else return x;
}

void imaging::color::clamp()
{
    r = ::clamp(r);
    g = ::clamp(g);
    b = ::clamp(b);
}

color imaging::color::clamped() const
{
    color copy = *this;
    copy.clamp();
    return copy;
}

color imaging::operator +(const color& c1, const color& c2)
{
    return color(c1.r + c2.r, c1.g + c2.g, c1.b + c2.b);
}

color imaging::operator *(const color& c, double f)
{
    return color(c.r * f, c.g * f, c.b * f);
}

color imaging::operator *(double f, const color& c)
{
    return c * f;
}

color imaging::operator /(const color& c, double f)
{
    return c * (1 / f);
}

color& imaging::operator +=(color& c1, const color& c2)
{
    return c1 = c1 + c2;
}

color& imaging::operator *=(color& c, double f)
{
    return c = c * f;
}

color& imaging::operator /=(color& c, double f)
{
    return c = c / f;
}

bool imaging::operator ==(const color& c1, const color& c2)
{
    return c1.r == math::approx<double>(c2.r) && c1.g == math::approx<double>(c2.g) && c1.b == math::approx<double>(c2.b);
}

bool imaging::operator !=(const color& c1, const color& c2)
{
    return !(c1 == c2);
}

std::ostream& imaging::operator <<(std::ostream& out, const color& c)
{
    return out << "RGB[" << c.r << "," << c.g << "," << c.b << "]";
}
