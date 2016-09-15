#pragma once

#include "animation/animation.h"
#include <cmath>


namespace animation
{
    template<typename T>
    Animation<T> loop(Animation<T> a)
    {
        std::function<T(TimeStamp)> lambda = [a](TimeStamp now)
        {
            double now_in_seconds = now.seconds();
            double duration_in_seconds = a.duration().seconds();
            double remainder = fmod(now_in_seconds, duration_in_seconds);
            TimeStamp looped_now = TimeStamp::from_seconds_since_epoch(remainder);

            return a(looped_now);
        };

        return make_animation(math::from_lambda(lambda), Duration::infinite());
    }
}
