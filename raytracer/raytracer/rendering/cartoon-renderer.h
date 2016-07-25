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
                CartoonRenderer(unsigned, unsigned, raytracer::Sampler, RayTracer, std::shared_ptr<util::Looper>, unsigned, double);

                std::shared_ptr<imaging::Bitmap> render(const Scene&) const override;

            private:
                unsigned m_shade_count;
                double m_stroke_thickness;
            };
        }

        Renderer cartoon(unsigned, unsigned, raytracer::Sampler, RayTracer, std::shared_ptr<util::Looper>, unsigned, double);
    }
}