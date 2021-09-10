#include "patterns/spiral-pattern.h"
#include "patterns/polar-pattern.h"


using namespace patterns;
using namespace math;


Pattern2D patterns::spiral(double thickness, unsigned n, double spacing)
{
    std::function<bool(double, Angle)> function = [=](double radius, Angle theta) -> bool
    {
        auto& limit = spacing;
        auto r = fmod(radius, limit);
        auto a = (theta.degrees() + 180) / 360 * limit;

        r = fmod(r, limit);
        a = fmod(n * a, limit);

        return fabs(r - a) < thickness || fabs(r + limit - a) < thickness || fabs(r - limit - a) < thickness;
    };

    return make_pattern(function);
}
