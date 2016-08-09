#pragma once

#include "animation/animation.h"


namespace animation
{
    Animation<math::Point3D> circular(const math::Point3D&, const math::Point3D&, const math::Vector3D&, const math::Interval<math::Angle>&, const Duration&);
}