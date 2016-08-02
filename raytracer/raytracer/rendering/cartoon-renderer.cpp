#include "rendering/cartoon-renderer.h"
#include "data-structures/grid.h"
#include <vector>

using namespace imaging;
using namespace math;
using namespace raytracer;
using namespace raytracer::rendering;


namespace
{
    class CartoonRenderer : public raytracer::rendering::_private_::RendererImplementation
    {
    public:
        CartoonRenderer(
            unsigned horizontal_resolution,
            unsigned vertical_resolution,
            raytracer::Sampler sampler,
            RayTracer ray_tracer,
            std::shared_ptr<util::Looper> looper,
            unsigned shade_count,
            double stroke_thickness)
            : RendererImplementation(horizontal_resolution, vertical_resolution, sampler, ray_tracer, looper)
            , m_shade_count(shade_count)
            , m_stroke_thickness(stroke_thickness)
        {
            // NOP
        }

        std::shared_ptr<imaging::Bitmap> render(const Scene& scene) const override
        {
            auto result = std::make_shared<Bitmap>(m_horizontal_resolution, m_vertical_resolution);
            Bitmap& bitmap = *result;
            Rectangle2D window(Point2D(0, 0), Vector2D(1, 0), Vector2D(0, 1));
            Rasterizer window_rasterizer(window, bitmap.width(), bitmap.height());
            data::Grid<std::vector<std::pair<unsigned, Point2D>>> group_grid(m_horizontal_resolution, m_vertical_resolution);

            for_each_pixel([&](Position pixel_coordinates) {
                Position bitmap_coordinates(pixel_coordinates.x, bitmap.height() - pixel_coordinates.y - 1);
                math::Rectangle2D pixel_rectangle = window_rasterizer[pixel_coordinates];
                imaging::Color c = imaging::colors::black();
                unsigned sample_count = 0;

                m_sampler->sample(pixel_rectangle, [&](const Point2D& p) {
                    scene.camera->enumerate_rays(p, [&](const Ray& ray) {
                        TraceResult tr = m_ray_tracer->trace(scene, ray);
                        group_grid[pixel_coordinates].push_back(std::make_pair(tr.group_id, p));
                        c += tr.color.quantized(m_shade_count);
                        ++sample_count;
                    });
                });

                c /= sample_count;

                bitmap[bitmap_coordinates] = c;
            });


            for (unsigned y = 0; y != bitmap.height(); ++y)
            {
                for (unsigned x = 0; x != bitmap.width(); ++x)
                {
                    Position pixel_coordinates(x, y);
                    Position bitmap_coordinates(x, bitmap.height() - y - 1);
                    unsigned border_count = 0;

                    for (auto& pair : group_grid[pixel_coordinates])
                    {
                        unsigned current_id = pair.first;
                        Point2D current_xy = pair.second;
                        bool is_border = false;

                        group_grid.around(pixel_coordinates, unsigned(ceil(m_stroke_thickness * std::max(m_horizontal_resolution, m_vertical_resolution))), [&](const Position& neighbor_pixel_position) {
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

                    double border_percentage = double(border_count) / group_grid[pixel_coordinates].size();

                    if (border_percentage > 0)
                    {
                        if (border_percentage < 1)
                        {
                            bitmap[bitmap_coordinates] *= (1 - border_percentage);
                        }
                        else
                        {
                            bitmap[bitmap_coordinates] = colors::black();
                        }
                    }
                }
            }

            return result;
        }

    private:
        unsigned m_shade_count;
        double m_stroke_thickness;
    };
}

Renderer raytracer::rendering::cartoon(unsigned horizontal_resolution, unsigned vertical_resolution, raytracer::Sampler sampler, RayTracer ray_tracer, std::shared_ptr<util::Looper> looper, unsigned shade_count, double stroke_thickness)
{
    return Renderer(std::make_shared<CartoonRenderer>(horizontal_resolution, vertical_resolution, sampler, ray_tracer, looper, shade_count, stroke_thickness));
}
