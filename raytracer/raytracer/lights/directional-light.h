#pragma once

#include "lights/point-light.h"
#include <memory>


namespace raytracer
{
    namespace lights
    {
        namespace _private_
        {
            class DirectionalLight : public LightSourceImplementation
            {
            public:
                DirectionalLight(const math::Vector3D&, const imaging::color&);

                std::vector<LightRay> lightrays_to(const math::Point3D&) const override;

            private:
                math::Vector3D m_direction;
                imaging::color m_color;
            };
        }

        LightSource directional(const math::Vector3D&, const imaging::color&);
    }
}