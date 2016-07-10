#pragma once

#include "rendering/renderer.h"

namespace raytracer
{
    namespace rendering
    {
        namespace _private_
        {
            class MultithreadedRenderer : public Renderer
            {
            public:
                MultithreadedRenderer(unsigned, unsigned, raytracer::samplers::Sampler, std::shared_ptr<RayTracer>, unsigned);

                imaging::Bitmap render(const Scene&) const override;

            private:
                unsigned m_thread_count;
            };
        }

        std::shared_ptr<_private_::Renderer> multithreaded(unsigned, unsigned, raytracer::samplers::Sampler, std::shared_ptr<RayTracer>, unsigned);
    }
}