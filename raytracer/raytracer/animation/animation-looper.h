#pragma once

#include "animation/animation.h"


namespace animation
{
    template<typename T>
    Animation<T> loop(Animation<T> a)
    {
        std::function<T(TimeStamp)> lambda = [a](TimeStamp now)
        {
            double now_in_seconds = now.seconds();
            double duration_in_seconds = a.duration().seconds();
            double remainder = now_in_seconds % duration_in_seconds;
            double looped_now = TimeStamp::from_epoch(Duration::from_seconds(looped_now));

            return a(looped_now);
        };

        return make_animation(from_lambda(lambda), Duration::infinite());
    }
}