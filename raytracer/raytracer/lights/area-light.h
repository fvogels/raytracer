#pragma once

#include "lights/point-light.h"
#include "math/rectangle3d.h"
#include "sampling/sampler.h"
#include <memory>


namespace raytracer
{
    namespace lights
    {
        namespace _private_
        {
            class AreaLight : public LightSourceImplementation
            {
            public:
                AreaLight(const math::Rectangle3D&, raytracer::Sampler sampler, const imaging::color&);

                std::vector<LightRay> lightrays_to(const math::Point3D&) const override;

            private:
                math::Rectangle3D m_area;
                raytracer::Sampler m_sampler;
                imaging::color m_color;
            };
        }

        LightSource area(const math::Rectangle3D&, raytracer::Sampler, const imaging::color&);
    }
}