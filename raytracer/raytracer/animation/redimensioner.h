#pragma once

#include "animation/animation.h"
#include "math/function.h"


namespace animation
{
    template<typename T>
    math::Function<T(const math::Point2D&)> xyz_to_tyz(math::Function<T(const math::Point3D&)> function, TimeStamp now)
    {
        std::function<T(const Point2D&)> lambda = [=](const Point2D& p) -> T {
            return function(now.seconds(), p.x(), p.y());
        };

        return from_lambda(lambda);
    }

    template<typename T>
    math::Function<T(const math::Point2D&)> xyz_to_xtz(math::Function<T(const math::Point3D&)> function, TimeStamp now)
    {
        std::function<T(const Point2D&)> lambda = [=](const Point2D& p) -> T {
            return function(p.x(), now.seconds(), p.y());
        };

        return from_lambda(lambda);
    }

    template<typename T>
    math::Function<T(const math::Point2D&)> xyz_to_xyt(math::Function<T(const math::Point3D&)> function, TimeStamp now)
    {
        std::function<T(const Point2D&)> lambda = [=](const Point2D& p) -> T {
            return function(p.x(), p.y(), now.seconds());
        };

        return from_lambda(lambda);
    }

    template<typename T>
    math::Function<T(const math::Point3D&)> xyz_to_xyzt(math::Function<T(const math::Point3D&)> function, TimeStamp now)
    {
        std::function<T(const Point3D&)> lambda = [=](const Point3D& p) -> T {
            double delta = now.seconds() + (p.x() + p.y() + p.z()) / 3;

            return function(Point3D(p.x() + delta, p.y() + delta, p.z() + delta));
        };

        return from_lambda(lambda);
    }
}