#pragma once

#include "rendering/renderer.h"


namespace raytracer
{
    namespace rendering
    {
        namespace _private_
        {
            class SingleThreadedRenderer : public RendererImplementation
            {
            public:
                using RendererImplementation::RendererImplementation;

                std::shared_ptr<imaging::Bitmap> render(const Scene&) const override;
            };
        }

        Renderer single_threaded(unsigned, unsigned, raytracer::Sampler, RayTracer);
    }
}