#pragma once

#include "animation/animation.h"


namespace animation
{
    template<typename T>
    Animation<T> ease(Animation<T> animation, math::functions::EasingFunction easing_function)
    {
        return preprocess<T>(timestamp_to_seconds() >> easing_function >> seconds_to_timestamp(), animation);
    }
}