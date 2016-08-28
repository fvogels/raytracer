#include "renderers/renderer.h"

using namespace math;
using namespace util;


raytracer::renderers::_private_::RendererImplementation::RendererImplementation(unsigned horizontal_resolution, unsigned vertical_resolution, raytracer::Sampler sampler, RayTracer ray_tracer, std::shared_ptr<Looper> looper)
    : m_horizontal_resolution(horizontal_resolution), m_vertical_resolution(vertical_resolution), m_sampler(sampler), m_ray_tracer(ray_tracer), m_looper(looper)
{
    // NOP
}

void raytracer::renderers::_private_::RendererImplementation::for_each_pixel(std::function<void(Position)> callback) const
{
    m_looper->loop(m_vertical_resolution, [this, callback](unsigned y) {
        for (unsigned x = 0; x != m_horizontal_resolution; ++x)
        {
            callback(Position(x, y));
        }
    });
}