#pragma once

#include "lights/point-light.h"
#include "imaging/color.h"
#include "math/point.h"
#include <memory>

namespace raytracer
{
    namespace lights
    {
        LightSource omnidirectional(const math::Point3D&, const imaging::Color&);
    }
}