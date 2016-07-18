#include "rendering/cartoon-renderer.h"
#include "data-structures/grid.h"
#include <thread>
#include <atomic>

using namespace imaging;
using namespace math;
using namespace raytracer;
using namespace raytracer::rendering;


raytracer::rendering::_private_::CartoonRenderer::CartoonRenderer(
    unsigned horizontal_resolution, 
    unsigned vertical_resolution, 
    raytracer::Sampler sampler, 
    RayTracer ray_tracer, 
    unsigned thread_count, 
    double stroke_thickness)
    : RendererImplementation(horizontal_resolution, vertical_resolution, sampler, ray_tracer)
    , m_thread_count(thread_count)
    , m_stroke_thickness(stroke_thickness)
{
    // NOP
}

Bitmap raytracer::rendering::_private_::CartoonRenderer::render(const Scene& scene) const
{
    Bitmap bitmap(m_horizontal_resolution, m_vertical_resolution);
    data::Grid<unsigned> id_grid(m_horizontal_resolution, m_vertical_resolution);
    Rectangle2D window(Point2D(0, 0), Vector2D(1, 0), Vector2D(0, 1));
    Rasterizer window_rasterizer(window, bitmap.width(), bitmap.height());

    std::atomic<unsigned> j(0);
    std::vector<std::thread> threads;

    for (int k = 0; k != m_thread_count; ++k)
    {
        threads.push_back(std::thread([&]() {
            unsigned current;

            while ((current = j++) < bitmap.height())
            {
                int y = bitmap.height() - current - 1;

                for (int i = 0; i != bitmap.width(); ++i)
                {
                    int x = i;

                    color c = render_pixel(window_rasterizer, x, y, scene);
                    c.quantize(16);

                    bitmap[position(i, current)] = c;
                }
            }
        }));
    }

    for (auto& thread : threads)
    {
        thread.join();
    }

    return bitmap;
}

Renderer raytracer::rendering::cartoon(unsigned horizontal_resolution, unsigned vertical_resolution, raytracer::Sampler sampler, RayTracer ray_tracer, unsigned thread_count, double stroke_thickness)
{
    return Renderer(std::make_shared<_private_::CartoonRenderer>(horizontal_resolution, vertical_resolution, sampler, ray_tracer, thread_count, stroke_thickness));
}