#pragma once

#include "raytracing/ray-tracer.h"
#include <memory>


namespace raytracer
{
    namespace raytracers
    {
        namespace _private_
        {
            class MonteCarloRayTracer : public RayTracer
            {
            public:
                MonteCarloRayTracer(unsigned recursion_limit = 2);

                imaging::color trace(const Scene&, const math::Ray&) const override;

            private:
                imaging::color trace(const Scene&, const math::Ray&, unsigned) const;

                unsigned m_recursion_limit;
            };
        }

        std::shared_ptr<RayTracer> monte_carlo(unsigned recursion_limit = 2);
    }
}