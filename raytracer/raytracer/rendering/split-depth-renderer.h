#pragma once

#include "rendering/renderer.h"


namespace raytracer
{
    namespace rendering
    {
        namespace _private_
        {
            class SplitDepthRenderer : public RendererImplementation
            {
            public:
                SplitDepthRenderer(unsigned, unsigned, raytracer::Sampler, RayTracer, std::shared_ptr<util::Looper>);

                std::shared_ptr<imaging::Bitmap> render(const Scene&) const override;

            private:
                bool is_on_split(const Position&) const;
                bool is_in_front_of_split(double) const;

                double m_stroke_thickness;
            };
        }

        Renderer split_depth(unsigned, unsigned, raytracer::Sampler, RayTracer, std::shared_ptr<util::Looper>);
    }
}