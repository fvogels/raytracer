#include "rendering/edge-renderer.h"
#include "data-structures/grid.h"
#include "easylogging++.h"
#include <vector>

using namespace imaging;
using namespace math;
using namespace raytracer;
using namespace raytracer::renderers;


namespace
{
    class EdgeRenderer : public raytracer::renderers::_private_::RendererImplementation
    {
    public:
        EdgeRenderer(
            unsigned horizontal_resolution,
            unsigned vertical_resolution,
            raytracer::Sampler sampler,
            RayTracer ray_tracer,
            std::shared_ptr<util::Looper> looper,
            double stroke_thickness)
            : RendererImplementation(horizontal_resolution, vertical_resolution, sampler, ray_tracer, looper)
            , m_stroke_thickness(stroke_thickness)
        {
            // NOP
        }

        std::shared_ptr<imaging::Bitmap> render(const Scene& scene) const
        {
            Rectangle2D window(Point2D(0, 0), Vector2D(1, 0), Vector2D(0, 1));
            Rasterizer window_rasterizer(window, m_horizontal_resolution, m_vertical_resolution);
            data::Grid<std::vector<std::pair<unsigned, Point2D>>> group_grid(m_horizontal_resolution, m_vertical_resolution);

            for_each_pixel([&](Position pixel_coordinates) {
                assert(pixel_coordinates.x < m_horizontal_resolution);
                assert(pixel_coordinates.y < m_vertical_resolution);

                math::Rectangle2D pixel_rectangle = window_rasterizer[pixel_coordinates];
                std::vector<std::pair<unsigned, Point2D>> data;

                m_sampler->sample(pixel_rectangle, [&](const Point2D& p) {
                    scene.camera->enumerate_rays(p, [&](const Ray& ray) {
                        TraceResult tr = m_ray_tracer->trace(scene, ray);

                        data.push_back(std::make_pair(tr.group_id, p));
                    });
                });

                group_grid[pixel_coordinates] = data;
            });

            auto result = std::make_shared<Bitmap>(m_horizontal_resolution, m_vertical_resolution);
            Bitmap& bitmap = *result;
            bitmap.clear(colors::white());

            LOG(DEBUG) << "Finding edges";

            for_each_pixel([&](Position pixel_coordinates) {
                Position bitmap_coordinates(pixel_coordinates.x, bitmap.height() - pixel_coordinates.y - 1);
                unsigned border_count = 0;

                for (auto& pair : group_grid[pixel_coordinates])
                {
                    unsigned current_id = pair.first;
                    Point2D current_xy = pair.second;
                    bool is_border = false;

                    group_grid.around(pixel_coordinates, unsigned(ceil(m_stroke_thickness * std::max(m_horizontal_resolution, m_vertical_resolution))), [&](const Position& neighbor_pixel_coordinates) {
                        for (auto& pair : group_grid[neighbor_pixel_coordinates])
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

                double border_percentage = double(border_count) / group_grid[pixel_coordinates].size();

                if (border_percentage > 0)
                {
                    if (border_percentage < 1)
                    {
                        bitmap[bitmap_coordinates] = colors::white() * (1 - border_percentage);
                    }
                    else
                    {
                        bitmap[bitmap_coordinates] = colors::black();
                    }
                }
            });

            return result;
        }

    private:
        double m_stroke_thickness;
    };
}

Renderer raytracer::renderers::edge(unsigned horizontal_resolution, unsigned vertical_resolution, raytracer::Sampler sampler, RayTracer ray_tracer, std::shared_ptr<util::Looper> looper, double stroke_thickness)
{
    return Renderer(std::make_shared<EdgeRenderer>(horizontal_resolution, vertical_resolution, sampler, ray_tracer, looper, stroke_thickness));
}
