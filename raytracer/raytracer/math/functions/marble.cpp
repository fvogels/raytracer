#define _USE_MATH_DEFINES
#include "math/functions/marble.h"
#include "math/functions/perlin.h"
#include "math/vector.h"

using namespace math;
using namespace math::functions;


Noise2D math::functions::marble2d(unsigned octaves, double turbulence)
{
    auto noise = perlin2d(15, octaves);

    std::function<double(const Point2D&)> lambda = [noise, turbulence](const Point2D& p) -> double {
        double t = p.x() + p.y();
        return std::abs(sin(360_degrees * t + 360_degrees * turbulence * noise(p)));
    };

    return from_lambda<double, const Point2D&>(lambda);
}

Noise3D math::functions::marble3d(unsigned octaves, double turbulence)
{
    auto noise = perlin3d(71, octaves);

    std::function<double(const Point3D&)> lambda = [noise, turbulence](const Point3D& p) -> double {
        double t = p.x() + p.y();
        return std::abs(sin(360_degrees * t + 360_degrees * turbulence * noise(p)));
    };

    return from_lambda<double, const Point3D&>(lambda);
}
