#pragma once

#include "animation/animation.h"


namespace animation
{
    template<typename T>
    Animation<T> sequence(Animation<T> a, Animation<T> b)
    {
        std::function<T(TimeStamp)> lambda = [a, b](TimeStamp now)
        {
            TimeStamp start_b = TimeStamp::from_epoch(a.duration());

            if (now < start_b)
            {
                return a(now);
            }
            else
            {
                return b(now - a.duration());
            }
        };

        return make_animation(from_lambda(lambda), a.duration() + b.duration());
    }
}