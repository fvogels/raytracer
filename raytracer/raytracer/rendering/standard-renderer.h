#pragma once

#include "rendering/renderer.h"
#include "rendering/renderer.h"
#include <functional>


namespace raytracer
{
    namespace rendering
    {
        namespace _private_
        {
            class StandardRenderer : public RendererImplementation
            {
            public:
                StandardRenderer(unsigned, unsigned, raytracer::Sampler, RayTracer, std::shared_ptr<util::Looper>);

                std::shared_ptr<imaging::Bitmap> render(const Scene&) const override;

            private:
                imaging::Color render_pixel(const math::Rasterizer&, const Position&, const Scene&) const;

                unsigned m_thread_count;
            };
        }

        Renderer standard(unsigned, unsigned, raytracer::Sampler, RayTracer, std::shared_ptr<util::Looper>);
    }
}