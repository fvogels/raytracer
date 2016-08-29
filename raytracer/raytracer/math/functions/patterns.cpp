#include "math/functions/patterns.h"
#include "math/functions.h"
#include <cmath>

using namespace math;


Function<bool(const Point2D&)> math::functions::grid(double thickness)
{
    std::function<bool(const Point2D&)> function = [thickness](const Point2D& p)
    {
        auto x = p.x();
        auto y = p.y();

        return std::abs(x - round(x)) < thickness / 2 || std::abs(y - round(y)) < thickness / 2;
    };

    return from_lambda<bool, const Point2D&>(function);
}

Function<bool(const Point2D&)> math::functions::polka(double radius)
{
    std::function<bool(const Point2D&)> function = [radius](const Point2D& p)
    {
        auto x = p.x();
        auto y = p.y();

        auto fx = x - floor(x);
        auto fy = y - floor(y);

        Point2D fp(fx, fy);

        return distance(fp, Point2D(0.5, 0.5)) < radius;
    };

    return from_lambda<bool, const Point2D&>(function);
}

Function<bool(const Point2D&)> math::functions::polka2(unsigned density, unsigned seed)
{
    auto voronoi = math::voronoi2d(density);

    std::function<bool(const Point2D&)> function = [voronoi](const Point2D& p)
    {
        auto closest = voronoi.closest_to(p);
        auto closest_to_closest = voronoi.second_closest_to(closest);
        auto radius = distance(closest, closest_to_closest) * 0.45;

        return distance(p, closest) < radius;
    };

    return from_lambda<bool, const Point2D&>(function);
}
