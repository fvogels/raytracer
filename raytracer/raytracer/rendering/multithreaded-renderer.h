#pragma once

#include "rendering/renderer.h"

namespace raytracer
{
    namespace rendering
    {
        namespace _private_
        {
            class MultithreadedRenderer : public RendererImplementation
            {
            public:
                MultithreadedRenderer(unsigned, unsigned, raytracer::Sampler, RayTracer, unsigned);

                imaging::Bitmap render(const Scene&) const override;

            private:
                unsigned m_thread_count;
            };
        }

        Renderer multithreaded(unsigned, unsigned, raytracer::Sampler, RayTracer, unsigned);
    }
}