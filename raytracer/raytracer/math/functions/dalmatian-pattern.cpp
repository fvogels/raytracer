#include "math/functions/dalmatian-pattern.h"
#include "math/functions.h"
#include <cmath>

using namespace math;


Function<bool(const Point2D&)> math::functions::dalmatian(unsigned density, unsigned seed)
{
    auto voronoi = math::voronoi2d(density, seed);

    std::function<bool(const Point2D&)> function = [voronoi](const Point2D& p)
    {
        auto closest = voronoi.closest_to(p);
        auto closest_to_closest = voronoi.second_closest_to(closest);
        auto radius = distance(closest, closest_to_closest) * 0.45;

        return distance(p, closest) < radius;
    };

    return from_lambda<bool, const Point2D&>(function);
}
