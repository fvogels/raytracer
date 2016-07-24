#pragma once

#include "rendering/renderer.h"


namespace raytracer
{
    namespace rendering
    {
        namespace _private_
        {
            class EdgeRenderer : public RendererImplementation
            {
            public:
                EdgeRenderer(unsigned, unsigned, raytracer::Sampler, RayTracer, unsigned, double);

                std::shared_ptr<imaging::Bitmap> render(const Scene&) const override;

            private:
                unsigned m_thread_count;
                double m_stroke_thickness;
            };
        }

        Renderer edge(unsigned, unsigned, raytracer::Sampler, RayTracer, unsigned, double);
    }
}