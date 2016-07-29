#pragma once

#include "lights/point-light.h"
#include "math/function.h"
#include <memory>


namespace raytracer
{
    namespace lights
    {
        namespace _private_
        {
            
        }

        LightSource anisotropic(const math::Point3D&, const math::Vector3D&, math::Function<imaging::Color, double>);
        LightSource anisotropic(const math::Point3D&, const math::Point3D&, math::Function<imaging::Color, double>);
        LightSource anisotropic_monochromatic(const math::Point3D&, const math::Vector3D&, math::Function<double, double>, imaging::Color);
        LightSource anisotropic_monochromatic(const math::Point3D&, const math::Point3D&, math::Function<double, double>, imaging::Color);
    }
}