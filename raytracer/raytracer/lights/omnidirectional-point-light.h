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
            class OmnidirectionalPointLight : public PointLight
            {
            public:
                OmnidirectionalPointLight(const math::Point3D&, const imaging::color&);

            protected:
                LightRay cast_lightray_to(const math::Point3D&) const override;

            private:
                math::Point3D position;
                imaging::color m_color;
            };
        }

        std::shared_ptr<LightSource> omnidirectional(const math::Point3D&, const imaging::color&);
    }
}