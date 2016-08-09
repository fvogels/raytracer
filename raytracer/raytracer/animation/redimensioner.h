#pragma once

#include "animation/animation.h"
#include "math/function.h"


namespace animation
{
    template<typename T>
    animation::Animation<math::Function<T(const math::Point2D&)>> xyz_to_xyt(math::Function<T(const math::Point3D&)> function)
    {
        using result_type = math::Function<T(const math::Point2D&)>;

        std::function<result_type(TimeStamp)> lambda = [function](TimeStamp now) -> result_type
        {
            std::function<T(const Point2D&)> lambda2 = [now, function](const Point2D& p) -> T
            {
                return function(Point3D(p.x(), p.y(), now.seconds()));
            };

            result_type function = from_lambda(lambda2);

            return function;
        };

        return make_animation<result_type>(from_lambda(lambda), Duration::infinite());
    }

    template<typename T>
    animation::Animation<math::Function<T(const math::Point2D&)>> xyz_to_tyz(math::Function<T(const math::Point3D&)> function)
    {
        using result_type = math::Function<T(const math::Point2D&)>;

        std::function<result_type(TimeStamp)> lambda = [function](TimeStamp now) -> result_type
        {
            std::function<T(const Point2D&)> lambda2 = [now, function](const Point2D& p) -> T
            {
                return function(Point3D(now.seconds(), p.x(), p.y()));
            };

            result_type function = from_lambda(lambda2);

            return function;
        };

        return make_animation<result_type>(from_lambda(lambda), Duration::infinite());
    }

    template<typename T>
    animation::Animation<math::Function<T(const math::Point2D&)>> xyz_to_xtz(math::Function<T(const math::Point3D&)> function)
    {
        using result_type = math::Function<T(const math::Point2D&)>;

        std::function<result_type(TimeStamp)> lambda = [function](TimeStamp now) -> result_type
        {
            std::function<T(const Point2D&)> lambda2 = [now, function](const Point2D& p) -> T
            {
                return function(Point3D(p.x(), now.seconds(), p.y()));
            };

            result_type function = from_lambda(lambda2);

            return function;
        };

        return make_animation<result_type>(from_lambda(lambda), Duration::infinite());
    }
}