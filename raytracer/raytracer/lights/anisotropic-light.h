#pragma once

#include "lights/point-light.h"
#include "math/function.h"
#include <memory>


namespace raytracer
{
    namespace lights
    {
        LightSource anisotropic(const math::Point3D&, const math::Vector3D&, const math::Vector3D&, math::Function<imaging::Color(math::Angle, math::Angle)>);
        LightSource anisotropic(const math::Point3D&, const math::Point3D&, const math::Vector3D&, math::Function<imaging::Color(math::Angle, math::Angle)>);
        LightSource anisotropic(const math::Point3D&, const math::Vector3D&, math::Function<imaging::Color(math::Angle)>);
        LightSource anisotropic(const math::Point3D&, const math::Point3D&, math::Function<imaging::Color(math::Angle)>);
        LightSource anisotropic_monochromatic(const math::Point3D&, const math::Vector3D&, math::Function<double(math::Angle)>, imaging::Color);
        LightSource anisotropic_monochromatic(const math::Point3D&, const math::Point3D&, math::Function<double(math::Angle)>, imaging::Color);
    }
}