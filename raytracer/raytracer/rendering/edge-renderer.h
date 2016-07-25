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
                EdgeRenderer(unsigned, unsigned, raytracer::Sampler, RayTracer, std::shared_ptr<util::Looper>, double);

                std::shared_ptr<imaging::Bitmap> render(const Scene&) const override;

            private:
                double m_stroke_thickness;
            };
        }

        Renderer edge(unsigned, unsigned, raytracer::Sampler, RayTracer, std::shared_ptr<util::Looper>, double);
    }
}