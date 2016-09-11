#pragma once

#include "animation/animation.h"
#include "math/interval.h"


namespace animation
{
    template<typename T>
    Animation<T> animate(const math::Interval<T>& animation_interval, animation::Duration duration)
    {
        auto double_animation = basic(0, 1, duration);

        std::function<T(TimeStamp)> lambda = [double_animation, animation_interval](TimeStamp now) {
            double t = double_animation(now);

            assert(math::interval(0.0, 1.0).contains(t));

            return animation_interval.from_relative(double_animation(now));
        };

        return make_animation(math::from_lambda(lambda), duration);
    }

    template<typename T>
    Animation<T> animate(T from, T to, animation::Duration duration)
    {
        return animate(math::interval(from, to), duration);
    }
}