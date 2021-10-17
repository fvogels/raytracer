#include "renderers/simple-edge-renderer.h"
#include "renderers/renderer-base.h"
#include "data-structures/grid.h"
#include "easylogging++.h"
#include <vector>

using namespace imaging;
using namespace math;
using namespace raytracer;
using namespace raytracer::renderers;


namespace
{
    class SimpleEdgeRenderer : public raytracer::renderers::_private_::RendererBaseImplementation
    {
    public:
        SimpleEdgeRenderer(
            unsigned horizontal_size,
            unsigned vertical_size,
            raytracer::Sampler sampler,
            RayTracer ray_tracer,
            tasks::TaskScheduler scheduler,
            const Color& stroke_color,
            const Color& background_color)
            : RendererBaseImplementation(horizontal_size, vertical_size, sampler, ray_tracer, scheduler)
            , m_stroke_color(stroke_color)
            , m_background_color(background_color)
        {
            // NOP
        }

        std::shared_ptr<imaging::Bitmap> render(const Scene& scene) const
        {
            Rectangle2D window(Point2D(0, 0), Vector2D(1, 0), Vector2D(0, 1));
            Rasterizer window_rasterizer(window, m_horizontal_size, m_vertical_size);
            data::Grid<std::vector<unsigned>> group_grid(m_horizontal_size, m_vertical_size);

            for_each_pixel([&](Position2D pixel_coordinates) {
                assert(pixel_coordinates.x < m_horizontal_size);
                assert(pixel_coordinates.y < m_vertical_size);

                math::Rectangle2D pixel_rectangle = window_rasterizer[pixel_coordinates];
                std::vector<unsigned>& data = group_grid[pixel_coordinates];

                m_sampler->sample(pixel_rectangle, [&](const Point2D& p) {
                    scene.camera->enumerate_rays(p, [&](const Ray& ray) {
                        TraceResult tr = m_ray_tracer->trace(scene, ray);

                        data.push_back(tr.group_id);
                    });
                });
            });

            auto result = std::make_shared<Bitmap>(m_horizontal_size, m_vertical_size);
            Bitmap& bitmap = *result;
            bitmap.clear(m_background_color);

            for_each_pixel([&](Position2D pixel_coordinates) {
                Position2D bitmap_coordinates(pixel_coordinates.x, bitmap.height() - pixel_coordinates.y - 1);
                unsigned total_comparisons = 0;
                unsigned different_group_count = 0;

                for (auto current_id : group_grid[pixel_coordinates])
                {
                    group_grid.around(pixel_coordinates, 1, [&](const Position2D& neighbor_pixel_coordinates) {
                        for (auto neighbor_id : group_grid[neighbor_pixel_coordinates])
                        {
                            if (current_id != neighbor_id)
                            {
                                different_group_count++;
                            }

                            total_comparisons++;
                        }
                    });                    
                }

                double border_percentage = double(different_group_count) / double(total_comparisons);

                if (border_percentage > 0)
                {
                    if (border_percentage < 1)
                    {
                        bitmap[bitmap_coordinates] = (m_stroke_color * border_percentage) + (m_background_color * (1 - border_percentage));
                    }
                    else
                    {
                        bitmap[bitmap_coordinates] = m_stroke_color;
                    }
                }
            });

            return result;
        }

    private:
        Color m_stroke_color;
        Color m_background_color;
    };
}

Renderer raytracer::renderers::simple_edge(unsigned horizontal_size, unsigned vertical_size, raytracer::Sampler sampler, RayTracer ray_tracer, tasks::TaskScheduler scheduler, const Color& stroke_color, const Color& background_color)
{
    return Renderer(std::make_shared<SimpleEdgeRenderer>(horizontal_size, vertical_size, sampler, ray_tracer, scheduler, stroke_color, background_color));
}
