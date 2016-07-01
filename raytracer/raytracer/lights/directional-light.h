#pragma once

#include "lights/point-light.h"
#include <memory>


namespace raytracer
{
    namespace lights
    {
        namespace _private_
        {
            class DirectionalLight : public LightSource
            {
            public:
                DirectionalLight(const math::Vector3D&, const imaging::color&);

                std::vector<LightRay> lightrays_to(const math::Point3D&) const override;

            private:
                math::Vector3D m_direction;
                imaging::color m_color;
            };
        }

        std::shared_ptr<LightSource> directional(const math::Vector3D&, const imaging::color&);
    }
}