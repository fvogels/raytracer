#pragma once

#include "lights/point-light.h"
#include <memory>


namespace raytracer
{
    namespace lights
    {
        namespace _private_
        {
            class ConicalLight : public PointLight
            {
            public:
                ConicalLight(const math::Point3D&, const math::Vector3D&, math::Angle, const imaging::color&);

            protected:
                LightRay cast_lightray_to(const math::Point3D&) const;

            private:
                math::Vector3D m_direction;
                double m_min_cos;
                imaging::color m_color;
            };
        }

        std::shared_ptr<LightSource> conical(const math::Point3D&, const math::Vector3D&, math::Angle, const imaging::color&);
        std::shared_ptr<LightSource> conical(const math::Point3D&, const math::Point3D&, math::Angle, const imaging::color&);
    }
}