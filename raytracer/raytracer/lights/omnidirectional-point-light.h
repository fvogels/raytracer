#pragma once

#include "lights/point-light.h"
#include "imaging/color.h"
#include "math/point3d.h"
#include <memory>

namespace raytracer
{
    namespace lights
    {
        namespace _private_
        {
            class OmnidirectionalPointLight : public PointLightImplementation
            {
            public:
                OmnidirectionalPointLight(const math::Point3D&, const imaging::color&);

            protected:
                LightRay cast_lightray_to(const math::Point3D&) const override;

            private:
                imaging::color m_color;
            };
        }

        LightSource omnidirectional(const math::Point3D&, const imaging::color&);
    }
}