#pragma once

#include "animation/animation.h"


namespace animation
{
    template<typename T>
    Animation<T> invert(Animation<T> animation)
    {
        std::function<T(TimeStamp)> lambda = [animation](TimeStamp now)
        {
            TimeStamp end = TimeStamp::from_epoch(animation.duration());
            TimeStamp inverted_now = TimeStamp::from_seconds_since_epoch(end.seconds() - now.seconds());
            
            return animation(inverted_now);
        };

        return make_animation(math::from_lambda(lambda), animation.duration());
    }
}
