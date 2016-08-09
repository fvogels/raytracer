#pragma once

#include "animation/animation.h"


namespace animation
{
    template<typename T>
    Animation<T> interval(const math::Interval<T> iv, animation::Duration duration)
    {
        auto double_animation = straight(0, 1, duration);

        std::function<T(TimeStamp)> lambda = [double_animation, iv](TimeStamp now) {
            return iv.from_relative(double_animation(now));
        };

        return make_animation(math::from_lambda(lambda), duration);
    }

    template<typename T>
    Animation<T> interval(T from, T to, animation::Duration duration)
    {
        return interval(math::Interval<T>(from, to), duration);
    }
}