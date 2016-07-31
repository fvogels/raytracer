#pragma once

#include "imaging/color.h"
#include "math/ray.h"
#include "raytracing/scene.h"
#include <limits>


namespace raytracer
{
    struct TraceResult
    {
        static TraceResult no_hit()
        {
            return TraceResult(imaging::colors::black(), MISSING_ID, std::numeric_limits<double>::infinity() );
        }

        TraceResult(imaging::Color color, unsigned group_id, double distance_to_hit)
            : color(color), group_id(group_id), distance_to_hit(distance_to_hit) { }

        imaging::Color color;
        unsigned group_id;
        double distance_to_hit;
    };

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
        RayTracer()
            : RayTracer(nullptr) { }

        RayTracer(std::shared_ptr<raytracers::_private_::RayTracerImplementation> implementation)
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