#pragma once

#include "rendering/renderer.h"


namespace raytracer
{
    namespace rendering
    {
        namespace _private_
        {
            class SingleThreadedRenderer : public Renderer
            {
            public:
                using Renderer::Renderer;

                imaging::Bitmap render(const Scene&) const override;
            };
        }

        std::shared_ptr<Renderer> single_threaded(unsigned, unsigned, raytracer::samplers::Sampler, std::shared_ptr<RayTracer>);
    }
}