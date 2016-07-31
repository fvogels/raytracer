#include "rendering/standard-renderer.h"

using namespace imaging;
using namespace math;
using namespace raytracer;
using namespace raytracer::rendering;


raytracer::rendering::_private_::StandardRenderer::StandardRenderer(unsigned horizontal_resolution, unsigned vertical_resolution, raytracer::Sampler sampler, RayTracer ray_tracer, std::shared_ptr<util::Looper> looper)
    : RendererImplementation(horizontal_resolution, vertical_resolution, sampler, ray_tracer, looper)
{
    // NOP
}

std::shared_ptr<imaging::Bitmap> raytracer::rendering::_private_::StandardRenderer::render(const Scene& scene) const
{
    Rectangle2D window(point(0, 0), vector(1, 0), vector(0, 1));
    Rasterizer window_rasterizer(window, m_horizontal_resolution, m_vertical_resolution);
    auto result = std::make_shared<Bitmap>(m_horizontal_resolution, m_vertical_resolution);
    Bitmap& bitmap = *result;

    for_each_pixel([&](Position pixel_coordinates) {
        Color c = render_pixel(window_rasterizer, pixel_coordinates, scene);

        bitmap[pixel_coordinates] = c;
    });

    return result;
}

Renderer raytracer::rendering::standard(unsigned horizontal_resolution, unsigned vertical_resolution, raytracer::Sampler sampler, RayTracer ray_tracer, std::shared_ptr<util::Looper> looper)
{
    return Renderer(std::make_shared<rendering::_private_::StandardRenderer>(horizontal_resolution, vertical_resolution, sampler, ray_tracer, looper));
}