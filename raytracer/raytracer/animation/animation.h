#pragma once

#include "math/function.h"
#include "math/point3d.h"
#include "math/interval.h"
#include "math/angle.h"
#include "animation/duration.h"
#include "animation/time-stamp.h"


namespace animation
{
    template<typename T>
    class Animation
    {
    public:
        Animation(math::Function<T, TimeStamp> function, animation::Duration duration)
            : m_function(function), m_duration(duration) { }

        T operator ()(TimeStamp t)
        {
            return m_function(t);
        }

        Duration duration() const
        {
            return m_duration;
        }

    private:
        math::Function<T, TimeStamp> m_function;
        animation::Duration m_duration;
    };

    Animation<math::Point3D> circular_xz(double radius, const math::Interval<math::Angle>&, const Duration&);
    Animation<math::Point3D> circular(const math::Point3D&, const math::Point3D&, const math::Vector3D&, const math::Interval<math::Angle>&, const Duration&);
}