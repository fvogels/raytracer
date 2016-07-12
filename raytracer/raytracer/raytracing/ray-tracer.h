#pragma once

#include "imaging/color.h"
#include "math/ray.h"
#include "raytracing/scene.h"


namespace raytracer
{
    namespace raytracers
    {
        namespace _private_
        {
            class RayTracerImplementation
            {
            public:
                virtual imaging::color trace(const Scene&, const math::Ray&) const = 0;
            };
        }
    }

    class RayTracer
    {
    public:
        RayTracer(std::shared_ptr<raytracers::_private_::RayTracerImplementation> implementation)
            : m_implementation(implementation) { }

        const raytracers::_private_::RayTracerImplementation* operator ->() const
        {
            return m_implementation.get();
        }

    private:
        std::shared_ptr<raytracers::_private_::RayTracerImplementation> m_implementation;
    };
}