#pragma once

#include "animation/animation.h"


namespace animation
{
    template<typename T>
    Animation<T> limit(Animation<T> animation, Duration duration)
    {
        std::function<T(TimeStamp)> lambda = [animation](TimeStamp now)
        {
            return animation(now);
        };

        return make_animation(math::from_lambda(lambda), duration);
    }
}
