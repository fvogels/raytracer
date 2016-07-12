#include "rendering/multithreaded-renderer.h"
#include <thread>
#include <atomic>

using namespace imaging;
using namespace math;
using namespace raytracer;
using namespace raytracer::rendering;


raytracer::rendering::_private_::MultithreadedRenderer::MultithreadedRenderer(unsigned horizontal_resolution, unsigned vertical_resolution, raytracer::samplers::Sampler sampler, RayTracer ray_tracer, unsigned thread_count)
    : RendererImplementation(horizontal_resolution, vertical_resolution, sampler, ray_tracer), m_thread_count(thread_count)
{
    // NOP
}

Bitmap raytracer::rendering::_private_::MultithreadedRenderer::render(const Scene& scene) const
{
    Bitmap bitmap(m_horizontal_resolution, m_vertical_resolution);
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

Renderer raytracer::rendering::multithreaded(unsigned horizontal_resolution, unsigned vertical_resolution, raytracer::samplers::Sampler sampler, RayTracer ray_tracer, unsigned thread_count)
{
    return Renderer(std::make_shared<_private_::MultithreadedRenderer>(horizontal_resolution, vertical_resolution, sampler, ray_tracer, thread_count));
}