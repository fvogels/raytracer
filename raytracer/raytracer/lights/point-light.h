#pragma once

#include "lights/light-source.h"
#include "imaging/color.h"
#include "math/point.h"


namespace raytracer
{
    namespace lights
    {
        namespace _private_
        {
            class PointLightImplementation : public LightSourceImplementation
            {
            public:
                PointLightImplementation(const math::Point3D&);

                std::vector<LightRay> lightrays_to(const math::Point3D&) const override;

            protected:
                virtual LightRay cast_lightray_to(const math::Point3D&) const = 0;

                math::Point3D m_position;
            };
        }
    }
}