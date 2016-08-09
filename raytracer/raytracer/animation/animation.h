#pragma once

#include "math/function.h"
#include "math/point.h"
#include "math/interval.h"
#include "math/functions/easing-functions.h"
#include "math/angle.h"
#include "animation/duration.h"
#include "animation/time-stamp.h"


namespace animation
{
    template<typename T>
    class Animation
    {
    public:
        Animation(math::Function<T(TimeStamp)> function, animation::Duration duration)
            : m_function(function), m_duration(duration) { }

        T operator ()(TimeStamp t) const
        {
            return m_function(t);
        }

        math::Function<T(TimeStamp)> function() const
        {
            return m_function;
        }

        Duration duration() const
        {
            return m_duration;
        }

    private:
        math::Function<T(TimeStamp)> m_function;
        animation::Duration m_duration;
    };

    inline math::Function<TimeStamp(double)> seconds_to_timestamp()
    {
        std::function<TimeStamp(double)> lambda = [](double seconds) -> TimeStamp {
            return TimeStamp::from_epoch(Duration::from_seconds(seconds));
        };

        return math::from_lambda<TimeStamp, double>(lambda);
    }

    inline math::Function<double(TimeStamp)> timestamp_to_seconds()
    {
        std::function<double(TimeStamp)> lambda = [](TimeStamp ts) -> double {
            return ts.seconds();
        };

        return math::from_lambda<double, TimeStamp>(lambda);
    }

    template<typename T>
    Animation<T> make_animation(math::Function<T(TimeStamp)> function, animation::Duration duration)
    {
        return Animation<T>(function, duration);
    }

    template<typename T>
    Animation<T> preprocess(math::Function<TimeStamp(TimeStamp)> function, Animation<T> animation)
    {
        return make_animation<T>(function >> animation.function(), animation.duration());
    }

    template<typename T1, typename T2>
    Animation<T2> postprocess(Animation<T1> animation, math::Function<T2(T1)> function)
    {
        return make_animation<T2>(animation.function() >> function, animation.duration());
    }

    template<typename T>
    Animation<T> ease(Animation<T> animation, math::functions::EasingFunction easing_function)
    {
        return preprocess<T>(timestamp_to_seconds() >> easing_function >> seconds_to_timestamp(), animation);
    }

    Animation<double> straight(double, double, const Duration&);
}