#pragma once

#include "raytracers/ray-tracer-v3.h"
#include <memory>


namespace raytracer
{
    namespace raytracers
    {
        namespace _private_
        {
            class RayTracerV4 : public RayTracerV3
            {
            private:
                bool m_noisy;

            public:
                RayTracerV4(bool noisy = false)
                    : m_noisy(noisy) { }

            protected:
                imaging::Color process_light_ray(const Scene&, const MaterialProperties&, const Hit&, const math::Ray&, const LightRay&) const override;
            };
        }

        RayTracer v4();
        RayTracer noisy_v4();
    }
}