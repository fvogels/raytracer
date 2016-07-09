#include "rendering/renderer.h"


raytracer::rendering::Renderer::Renderer(unsigned horizontal_resolution, unsigned vertical_resolution, raytracer::samplers::Sampler sampler, std::shared_ptr<RayTracer> ray_tracer)
    : m_horizontal_resolution(horizontal_resolution), m_vertical_resolution(vertical_resolution), m_sampler(sampler), m_ray_tracer(ray_tracer) { }

imaging::color raytracer::rendering::Renderer::render_pixel(const math::Rasterizer& window_rasterizer, int x, int y, const Scene& scene) const
{
    math::Rectangle2D pixel_rectangle = window_rasterizer[position(x, y)];
    imaging::color c = imaging::colors::black();
    int sample_count = 0;

    m_sampler->sample(pixel_rectangle, [this, &c, &sample_count, &scene](const math::Point2D& p) {
        auto ray = scene.camera->create_ray(p);
        c += m_ray_tracer->trace(scene, ray);
        ++sample_count;
    });

    return c / sample_count;
}