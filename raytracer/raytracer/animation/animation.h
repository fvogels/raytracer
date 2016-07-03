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
        Animation(std::shared_ptr<math::FunctionBody<T, TimeStamp>> body, Duration duration)
            : m_body(body), m_duration(duration) { }

        T operator ()(TimeStamp t)
        {
            return m_body->evaluate(t);
        }

        Duration duration() const
        {
            return m_duration;
        }

    private:
        std::shared_ptr<math::FunctionBody<T, TimeStamp>> m_body;
        Duration m_duration;
    };

    // Animation<math::Point3D> circular_xz(math::Angle, math::Angle);

    // Animation<math::Point3D> circular_xz(const math::Point3D&, double, math::Angle, math::Angle, const Duration&);
}