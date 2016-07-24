#pragma once

#include "lights/point-light.h"
#include <memory>


namespace raytracer
{
    namespace lights
    {
        namespace _private_
        {
            class SpotLight : public PointLightImplementation
            {
            public:
                SpotLight(const math::Point3D&, const math::Vector3D&, math::Angle, const imaging::Color&);

            protected:
                LightRay cast_lightray_to(const math::Point3D&) const;

            private:
                math::Vector3D m_direction;
                double m_min_cos;
                imaging::Color m_color;
            };
        }

        LightSource spot(const math::Point3D&, const math::Vector3D&, math::Angle, const imaging::Color&);
        LightSource spot(const math::Point3D&, const math::Point3D&, math::Angle, const imaging::Color&);
    }
}