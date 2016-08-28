#pragma once

#include "imaging/color.h"
#include "math/ray.h"
#include "raytracing/scene.h"
#include "raytracing/trace-result.h"
#include <limits>


namespace raytracer
{
    namespace raytracers
    {
        namespace _private_
        {
            class RayTracerImplementation
            {
            public:
                virtual TraceResult trace(const Scene&, const math::Ray&) const = 0;
            };
        }
    }

    class RayTracer
    {
    public:
        explicit RayTracer(std::shared_ptr<raytracers::_private_::RayTracerImplementation> implementation = nullptr)
            : m_implementation(implementation) { }

        const raytracers::_private_::RayTracerImplementation* operator ->() const
        {
            assert(m_implementation);

            return m_implementation.get();
        }

    private:
        std::shared_ptr<raytracers::_private_::RayTracerImplementation> m_implementation;
    };
}