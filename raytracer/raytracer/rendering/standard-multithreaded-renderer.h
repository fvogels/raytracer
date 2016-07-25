#pragma once

#include "rendering/renderer.h"
#include "rendering/multithreaded-renderer.h"
#include <functional>


namespace raytracer
{
    namespace rendering
    {
        namespace _private_
        {
            class StandardMultithreadedRenderer : public MultithreadedRenderer
            {
            public:
                StandardMultithreadedRenderer(unsigned, unsigned, raytracer::Sampler, RayTracer, unsigned);

                std::shared_ptr<imaging::Bitmap> render(const Scene&) const override;

            private:
                unsigned m_thread_count;
            };
        }

        Renderer standard_multithreaded(unsigned, unsigned, raytracer::Sampler, RayTracer, unsigned);
    }
}