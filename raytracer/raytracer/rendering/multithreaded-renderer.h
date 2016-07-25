#pragma once

#include "rendering/renderer.h"
#include <functional>


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

                std::shared_ptr<imaging::Bitmap> render(const Scene&) const override;

            protected:
                void for_each_pixel(std::function<void(const Position&)>) const;

            private:
                unsigned m_thread_count;
            };
        }

        Renderer multithreaded(unsigned, unsigned, raytracer::Sampler, RayTracer, unsigned);
    }
}