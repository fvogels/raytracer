#include "rendering/renderer.h"

using namespace math;


raytracer::rendering::_private_::RendererImplementation::RendererImplementation(unsigned horizontal_resolution, unsigned vertical_resolution, raytracer::Sampler sampler, RayTracer ray_tracer)
    : m_horizontal_resolution(horizontal_resolution), m_vertical_resolution(vertical_resolution), m_sampler(sampler), m_ray_tracer(ray_tracer)
{
    // NOP
}

imaging::color raytracer::rendering::_private_::RendererImplementation::render_pixel(const math::Rasterizer& window_rasterizer, int x, int y, const Scene& scene) const
{
    math::Rectangle2D pixel_rectangle = window_rasterizer[position(x, y)];
    imaging::color c = imaging::colors::black();
    int sample_count = 0;

    m_sampler->sample(pixel_rectangle, [this, &c, &sample_count, &scene](const Point2D& p) {
        scene.camera->enumerate_rays(p, [this, &c, &sample_count, &scene](const Ray& ray) {
            c += m_ray_tracer->trace(scene, ray).color;
            ++sample_count;
        });
    });

    return c / sample_count;
}