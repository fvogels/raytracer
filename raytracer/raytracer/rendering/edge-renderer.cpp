#define NOMINMAX
#include "rendering/edge-renderer.h"
#include "data-structures/grid.h"
#include "easylogging++.h"
#include <thread>
#include <atomic>
#include <vector>
#include <utility>

using namespace imaging;
using namespace math;
using namespace raytracer;
using namespace raytracer::rendering;


namespace
{
    double dist(const Position& p, const Position& q)
    {
        double dx = p.x - q.x;
        double dy = p.y - q.y;

        return sqrt(dx * dx + dy * dy);
    }
}


raytracer::rendering::_private_::EdgeRenderer::EdgeRenderer(
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

std::shared_ptr<imaging::Bitmap> raytracer::rendering::_private_::EdgeRenderer::render(const Scene& scene) const
{
    auto result = std::make_shared<Bitmap>(m_horizontal_resolution, m_vertical_resolution);
    Bitmap& bitmap = *result;
    Rectangle2D window(point(0, 0), vector(1, 0), vector(0, 1));
    Rasterizer window_rasterizer(window, bitmap.width(), bitmap.height());
    data::Grid<std::vector<std::pair<unsigned, Point2D>>> group_grid(m_horizontal_resolution, m_vertical_resolution);

    std::atomic<unsigned> j(0);
    std::vector<std::thread> threads;

    bitmap.clear(colors::white());

    LOG(DEBUG) << "Ray tracing";
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
                    Position pixel_coordinates(x, y);
                    math::Rectangle2D pixel_rectangle = window_rasterizer[Position(x, y)];

                    m_sampler->sample(pixel_rectangle, [&](const Point2D& p) {
                        scene.camera->enumerate_rays(p, [&](const Ray& ray) {
                            TraceResult tr = m_ray_tracer->trace(scene, ray);
                            group_grid[pixel_coordinates].push_back(std::make_pair(tr.group_id, p));
                        });
                    });

                }
            }
        }));
    }

    for (auto& thread : threads)
    {
        thread.join();
    }

    LOG(DEBUG) << "Finding edges";
    for (unsigned y = 0; y != bitmap.height(); ++y)
    {
        for (unsigned x = 0; x != bitmap.width(); ++x)
        {
            Position pixel_position(x, y);
            unsigned border_count = 0;

            for (auto& pair : group_grid[pixel_position])
            {
                unsigned current_id = pair.first;
                Point2D current_xy = pair.second;
                bool is_border = false;

                group_grid.around(pixel_position, unsigned(ceil(m_stroke_thickness * std::max(m_horizontal_resolution, m_vertical_resolution))), [&](const Position& neighbor_pixel_position) {
                    for (auto& pair : group_grid[neighbor_pixel_position])
                    {
                        unsigned neighbor_id = pair.first;
                        Point2D neighbor_xy = pair.second;

                        if (current_id != neighbor_id)
                        {
                            double dist = distance(current_xy, neighbor_xy);

                            if (dist < m_stroke_thickness)
                            {
                                is_border = true;
                            }
                        }
                    }
                });

                if (is_border)
                {
                    ++border_count;
                }
            }

            double border_percentage = double(border_count) / group_grid[pixel_position].size();

            if (border_percentage > 0)
            {
                if (border_percentage < 1)
                {
                    // bitmap[pixel_position] *= (1 - border_percentage);
                    bitmap[pixel_position] = colors::white() * (1 - border_percentage);
                }
                else
                {
                    bitmap[pixel_position] = colors::black();
                }
            }
        }
    }

    return result;
}

Renderer raytracer::rendering::edge(unsigned horizontal_resolution, unsigned vertical_resolution, raytracer::Sampler sampler, RayTracer ray_tracer, unsigned thread_count, double stroke_thickness)
{
    return Renderer(std::make_shared<_private_::EdgeRenderer>(horizontal_resolution, vertical_resolution, sampler, ray_tracer, thread_count, stroke_thickness));
}