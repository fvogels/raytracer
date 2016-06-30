#pragma once

#include "raytracing/ray-tracer.h"
#include <memory>


namespace raytracer
{
    namespace raytracers
    {
        namespace _private_
        {
            class FastRayTracer : public RayTracer
            {
            public:
                FastRayTracer(unsigned recursion_limit = 2);

                imaging::color trace(const Scene& scene, const math::Ray& ray) const override;                

            private:
                imaging::color trace(const Scene& scene, const math::Ray& ray, unsigned recursions_left) const;

                unsigned m_recursion_limit;
            };
        }

        std::shared_ptr<RayTracer> fast_ray_tracer(unsigned recursion_limit = 2);
    }
}