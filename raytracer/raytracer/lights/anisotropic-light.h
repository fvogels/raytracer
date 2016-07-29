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
            class AnisotropicLight : public PointLightImplementation
            {
            public:
                AnisotropicLight(const math::Point3D&, const math::Vector3D&, math::Function<imaging::Color, double> light_function);

            protected:
                LightRay cast_lightray_to(const math::Point3D&) const;

            private:
                math::Vector3D m_direction;
                math::Function<imaging::Color, double> m_light_function;
            };
        }

        LightSource anisotropic(const math::Point3D&, const math::Vector3D&, math::Function<imaging::Color, double>);
        LightSource anisotropic(const math::Point3D&, const math::Point3D&, math::Function<imaging::Color, double>);
        LightSource anisotropic_monochromatic(const math::Point3D&, const math::Vector3D&, math::Function<double, double>, imaging::Color);
        LightSource anisotropic_monochromatic(const math::Point3D&, const math::Point3D&, math::Function<double, double>, imaging::Color);
    }
}