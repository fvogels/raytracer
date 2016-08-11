#pragma once

#include "animation/animation.h"
#include "math/point.h"


namespace animation
{
    struct LissajousParameters
    {
        double amplitude;
        double frequency;
        math::Angle phase;
    };

    Animation<math::Point3D> lissajous(const LissajousParameters&, const LissajousParameters&, const LissajousParameters&, Duration);
}