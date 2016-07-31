#pragma once

#include "lights/point-light.h"
#include <memory>


namespace raytracer
{
    namespace lights
    {
        LightSource spot(const math::Point3D&, const math::Vector3D&, math::Angle, const imaging::Color&);
        LightSource spot(const math::Point3D&, const math::Point3D&, math::Angle, const imaging::Color&);
    }
}