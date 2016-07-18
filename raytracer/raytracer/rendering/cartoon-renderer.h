#pragma once

#include "rendering/renderer.h"


namespace raytracer
{
    namespace rendering
    {
        namespace _private_
        {
            class CartoonRenderer : public RendererImplementation
            {
            public:
                CartoonRenderer(unsigned, unsigned, raytracer::Sampler, RayTracer, unsigned, unsigned, double);

                imaging::Bitmap render(const Scene&) const override;

            private:
                unsigned m_thread_count;
                unsigned m_shade_count;
                double m_stroke_thickness;
            };
        }

        Renderer cartoon(unsigned, unsigned, raytracer::Sampler, RayTracer, unsigned, unsigned, double);
    }
}