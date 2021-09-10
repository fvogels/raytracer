#include "patterns/pattern-tiling.h"
#include "patterns/lambda-pattern.h"
#include <cmath>


using namespace math;
using namespace patterns;


Pattern2D patterns::tiling(Pattern2D pattern, double width, double height)
{
    std::function<bool(const Point2D&)> function = [=](const Point2D& point) -> bool {
        const auto x = fmod(fmod(point.x(), width) + width, width);
        const auto y = fmod(fmod(point.y(), height) + height, height);

        return pattern(Point2D(x, y));
    };

    return make_pattern(function);
}

Pattern2D patterns::wrong_tiling(Pattern2D pattern, double width, double height)
{
    std::function<bool(const Point2D&)> function = [=](const Point2D& point) -> bool {
        const auto x = fmod(point.x(), width);
        const auto y = fmod(point.y(), height);

        return pattern(Point2D(x, y));
    };

    return make_pattern(function);
}

Pattern2D patterns::tiling_x(Pattern2D pattern, double width)
{
    std::function<bool(const Point2D&)> function = [=](const Point2D& point) -> bool {
        const auto x = fmod(fmod(point.x(), width) + width, width);
        const auto y = point.y();

        return pattern(Point2D(x, y));
    };

    return make_pattern(function);
}

Pattern2D patterns::tiling_y(Pattern2D pattern, double height)
{
    std::function<bool(const Point2D&)> function = [=](const Point2D& point) -> bool {
        const auto x = point.x();
        const auto y = fmod(fmod(point.y(), height) + height, height);

        return pattern(Point2D(x, y));
    };

    return make_pattern(function);
}

Pattern3D patterns::tiling(Pattern3D pattern, double x_size, double y_size, double z_size)
{
    std::function<bool(const Point3D&)> function = [=](const Point3D& point) -> bool {
        const auto x = fmod(fmod(point.x(), x_size) + x_size, x_size);
        const auto y = fmod(fmod(point.y(), y_size) + y_size, y_size);
        const auto z = fmod(fmod(point.z(), z_size) + z_size, z_size);

        return pattern(Point3D(x, y, z));
    };

    return make_pattern(function);
}
