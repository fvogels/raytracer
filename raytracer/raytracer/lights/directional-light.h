#pragma once

#include "lights/point-light.h"
#include <memory>


namespace raytracer
{
    namespace lights
    {
        LightSource directional(const math::Vector3D&, const imaging::Color&);
    }
}