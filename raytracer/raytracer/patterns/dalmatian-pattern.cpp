#include "patterns/dalmatian-pattern.h"
#include "patterns/lambda-pattern.h"
#include "math/functions.h"
#include <cmath>

using namespace math;
using namespace patterns;


Pattern2D patterns::dalmatian2d(unsigned density, unsigned seed)
{
    auto voronoi = math::voronoi2d(density, seed);

    std::function<bool(const Point2D&)> function = [voronoi](const Point2D& p)
    {
        auto closest = voronoi.closest_to(p);
        auto closest_to_closest = voronoi.second_closest_to(closest);
        auto radius = distance(closest, closest_to_closest) * 0.45;

        return distance(p, closest) < radius;
    };

    return make_pattern(function);
}

Pattern3D patterns::dalmatian3d(unsigned density, unsigned seed)
{
    auto voronoi = math::voronoi3d(density, seed);

    std::function<bool(const Point3D&)> function = [voronoi](const Point3D& p)
    {
        auto closest = voronoi.closest_to(p);
        auto closest_to_closest = voronoi.second_closest_to(closest);
        auto radius = distance(closest, closest_to_closest) * 0.45;

        return distance(p, closest) < radius;
    };

    return make_pattern(function);
}
