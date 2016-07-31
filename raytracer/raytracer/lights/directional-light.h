#pragma once

#include "lights/point-light.h"
#include <memory>


namespace raytracer
{
    namespace lights
    {
        namespace _private_
        {
            
        }

        LightSource directional(const math::Vector3D&, const imaging::Color&);
    }
}