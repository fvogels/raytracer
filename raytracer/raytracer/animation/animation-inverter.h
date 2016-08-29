#pragma once

#include "animation/animation.h"


namespace animation
{
    template<typename T>
    Animation<T> invert(Animation<T> a)
    {
        std::function<T(TimeStamp)> lambda = [a](TimeStamp now)
        {
            TimeStamp end = TimeStamp::from_epoch(a.duration());
            TimeStamp inverted_now = end - now.seconds();
            
            return a(inverted_now);
        };

        return make_animation(from_lambda(lambda), a.duration() + b.duration());
    }
}