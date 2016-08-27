#pragma once

#include "rendering/renderer.h"
#include "math/math-plane.h"


namespace raytracer
{
    namespace renderers
    {
        Renderer split_depth(unsigned, unsigned, raytracer::Sampler, RayTracer, std::shared_ptr<util::Looper>, double, const math::Plane&);
        Renderer split_depth(unsigned, unsigned, raytracer::Sampler, RayTracer, std::shared_ptr<util::Looper>, double, const math::Point3D& eye, const math::Point3D& look_at);
    }
}