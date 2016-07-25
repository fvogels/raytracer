#pragma once

#include "rendering/multithreaded-renderer.h"


namespace raytracer
{
    namespace rendering
    {
        namespace _private_
        {
            class EdgeRenderer : public MultithreadedRenderer
            {
            public:
                EdgeRenderer(unsigned, unsigned, raytracer::Sampler, RayTracer, unsigned, double);

                std::shared_ptr<imaging::Bitmap> render(const Scene&) const override;

            private:
                double m_stroke_thickness;
            };
        }

        Renderer edge(unsigned, unsigned, raytracer::Sampler, RayTracer, unsigned, double);
    }
}