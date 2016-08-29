#pragma once

#include "imaging/bitmap.h"
#include "raytracers/scene.h"
#include "samplers/sampler.h"
#include "raytracers/ray-tracer.h"
#include "math/rasterizer.h"
#include "math/point.h"
#include "loopers/looper.h"

namespace raytracer
{
    namespace renderers
    {
        namespace _private_
        {
            class RendererImplementation
            {
            public:
                RendererImplementation(unsigned, unsigned, raytracer::Sampler, RayTracer, std::shared_ptr<util::Looper>);

                virtual std::shared_ptr<imaging::Bitmap> render(const Scene&) const = 0;

            protected:
                unsigned m_horizontal_resolution, m_vertical_resolution;
                raytracer::Sampler m_sampler;
                RayTracer m_ray_tracer;
                
                void for_each_pixel(std::function<void(Position)>) const;

            private:
                std::shared_ptr<util::Looper> m_looper;
            };
        }
    }

    class Renderer
    {
    public:
        explicit Renderer(std::shared_ptr<renderers::_private_::RendererImplementation> implementation = nullptr)
            : m_implementation(implementation) { }

        Renderer(const Renderer& r) = default;
        Renderer(Renderer&& r) = default;

        const renderers::_private_::RendererImplementation* operator ->() const { return m_implementation.get(); }

        operator bool() const { return m_implementation != nullptr; }

    private:
        std::shared_ptr<renderers::_private_::RendererImplementation> m_implementation;
    };
}