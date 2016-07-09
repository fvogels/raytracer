#pragma once

#include "imaging/bitmap.h"
#include "raytracing/scene.h"
#include "sampling/sampler.h"
#include "raytracing/ray-tracer.h"
#include "math/rasterizer.h"
#include "math/point2d.h"

namespace raytracer
{
    namespace rendering
    {
        class Renderer
        {
        public:
            Renderer(unsigned, unsigned, raytracer::samplers::Sampler, std::shared_ptr<RayTracer>);

            virtual imaging::Bitmap render(const Scene&) const = 0;

        protected:
            unsigned m_horizontal_resolution, m_vertical_resolution;
            raytracer::samplers::Sampler m_sampler;
            std::shared_ptr<RayTracer> m_ray_tracer;

            imaging::color render_pixel(const math::Rasterizer&, int, int, const Scene&) const;
        };
    }
}