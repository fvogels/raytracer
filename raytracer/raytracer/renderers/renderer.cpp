#include "renderers/renderer.h"

using namespace math;
using namespace loopers;

raytracer::renderers::_private_::RendererImplementation::RendererImplementation(unsigned horizontal_size, unsigned vertical_size, raytracer::Sampler sampler, RayTracer ray_tracer, std::shared_ptr<Looper> looper)
    : m_horizontal_size(horizontal_size), m_vertical_size(vertical_size), m_sampler(sampler), m_ray_tracer(ray_tracer), m_looper(looper)
{
    // NOP
}

void raytracer::renderers::_private_::RendererImplementation::for_each_pixel(std::function<void(Position)> callback) const
{
    m_looper->loop(m_vertical_size, [this, callback](unsigned y) {
        for (unsigned x = 0; x != m_horizontal_size; ++x)
        {
            callback(Position(x, y));
        }
    });
}