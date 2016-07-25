#include "rendering/multithreaded-renderer.h"
#include <thread>
#include <atomic>

using namespace imaging;
using namespace math;
using namespace raytracer;
using namespace raytracer::rendering;


raytracer::rendering::_private_::MultithreadedRenderer::MultithreadedRenderer(unsigned horizontal_resolution, unsigned vertical_resolution, raytracer::Sampler sampler, RayTracer ray_tracer, unsigned thread_count)
    : RendererImplementation(horizontal_resolution, vertical_resolution, sampler, ray_tracer), m_thread_count(thread_count)
{
    // NOP
}

std::shared_ptr<imaging::Bitmap> raytracer::rendering::_private_::MultithreadedRenderer::render(const Scene& scene) const
{
    Rectangle2D window(point(0, 0), vector(1, 0), vector(0, 1));
    Rasterizer window_rasterizer(window, m_horizontal_resolution, m_vertical_resolution);
    auto result = std::make_shared<Bitmap>(m_horizontal_resolution, m_vertical_resolution);
    Bitmap& bitmap = *result;

    for_each_pixel([&](const Position& position) {
        Color c = render_pixel(window_rasterizer, position, scene);
        bitmap[position] = c;
    });

    return result;
}

void raytracer::rendering::_private_::MultithreadedRenderer::for_each_pixel(std::function<void(const Position&)> callback) const
{
    std::atomic<unsigned> j(0);
    std::vector<std::thread> threads;

    for (int k = 0; k != m_thread_count; ++k)
    {
        threads.push_back(std::thread([&]() {
            unsigned current;

            while ((current = j++) < m_vertical_resolution)
            {
                const int y = m_vertical_resolution - current - 1;

                for (int x = 0; x != m_horizontal_resolution; ++x)
                {
                    callback(Position(x, y));
                }
            }
        }));
    }

    for (auto& thread : threads)
    {
        thread.join();
    }
}

Renderer raytracer::rendering::multithreaded(unsigned horizontal_resolution, unsigned vertical_resolution, raytracer::Sampler sampler, RayTracer ray_tracer, unsigned thread_count)
{
    return Renderer(std::make_shared<_private_::MultithreadedRenderer>(horizontal_resolution, vertical_resolution, sampler, ray_tracer, thread_count));
}