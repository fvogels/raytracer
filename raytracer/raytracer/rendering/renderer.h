#pragma once

#include "imaging/bitmap.h"
#include "raytracing/scene.h"
#include "sampling/sampler.h"
#include "raytracing/ray-tracer.h"
#include "math/rasterizer.h"
#include "math/point2d.h"

namespace raytracer
{
    namespace rendering
    {
        namespace _private_
        {
            class RendererImplementation
            {
            public:
                RendererImplementation(unsigned, unsigned, raytracer::Sampler, RayTracer);

                virtual std::shared_ptr<imaging::Bitmap> render(const Scene&) const = 0;

            protected:
                unsigned m_horizontal_resolution, m_vertical_resolution;
                raytracer::Sampler m_sampler;
                RayTracer m_ray_tracer;

                imaging::Color render_pixel(const math::Rasterizer&, const Position&, const Scene&) const;
            };
        }
    }

    class Renderer
    {
    public:
        Renderer(std::shared_ptr<rendering::_private_::RendererImplementation> implementation)
            : m_implementation(implementation) { }

        const rendering::_private_::RendererImplementation* operator ->() const { return m_implementation.get(); }

        operator bool() const { return m_implementation != nullptr; }

    private:
        std::shared_ptr<rendering::_private_::RendererImplementation> m_implementation;
    };
}