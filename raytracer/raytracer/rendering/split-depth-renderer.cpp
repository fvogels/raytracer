#include "rendering/split-depth-renderer.h"
#include <limits>
#include <cmath>

using namespace imaging;
using namespace math;
using namespace raytracer;
using namespace raytracer::rendering;


namespace
{
    class SplitDepthRenderer : public raytracer::rendering::_private_::RendererImplementation
    {
    public:
        SplitDepthRenderer(unsigned horizontal_resolution, unsigned vertical_resolution, raytracer::Sampler sampler, RayTracer ray_tracer, std::shared_ptr<util::Looper> looper, double split_thickness, double split_depth)
            : RendererImplementation(horizontal_resolution, vertical_resolution, sampler, ray_tracer, looper), m_split_thickness_in_pixels(int(split_thickness * horizontal_resolution)), m_split_depth(split_depth)
        {
            // NOP
        }

        std::shared_ptr<imaging::Bitmap> render(const Scene& scene) const
        {
            Rectangle2D window(point(0, 0), vector(1, 0), vector(0, 1));
            Rasterizer window_rasterizer(window, m_horizontal_resolution, m_vertical_resolution);
            auto result = std::make_shared<Bitmap>(m_horizontal_resolution, m_vertical_resolution);
            Bitmap& bitmap = *result;

            for_each_pixel([&](Position pixel_coordinates) {
                Position bitmap_coordinates(pixel_coordinates.x, bitmap.height() - pixel_coordinates.y - 1);

                math::Rectangle2D pixel_rectangle = window_rasterizer[pixel_coordinates];
                imaging::Color color = imaging::colors::black();
                int sample_count = 0;
                double smallest_distance = std::numeric_limits<double>::infinity();

                m_sampler->sample(pixel_rectangle, [this, &color, &sample_count, &scene, &smallest_distance](const Point2D& p) {
                    scene.camera->enumerate_rays(p, [this, &color, &sample_count, &scene, &smallest_distance](const Ray& ray) {
                        auto trace_result = m_ray_tracer->trace(scene, ray);
                        color += trace_result.color;

                        smallest_distance = std::min(smallest_distance, trace_result.distance_to_hit);

                        ++sample_count;
                    });
                });

                color /= sample_count;

                if (!is_on_split(pixel_coordinates) || is_in_front_of_split(smallest_distance))
                {
                    bitmap[bitmap_coordinates] = color;
                }
                else
                {
                    bitmap[bitmap_coordinates] = colors::white();
                }
            });

            return result;
        }

    private:
        bool is_on_split(const Position& pixel_coordinates) const
        {
            return abs(int(pixel_coordinates.x) - int(m_horizontal_resolution / 3)) < m_split_thickness_in_pixels / 2 ||
                abs(int(pixel_coordinates.x) - int(2 * m_horizontal_resolution / 3)) < m_split_thickness_in_pixels / 2;
        }

        bool is_in_front_of_split(double distance) const
        {
            return distance < m_split_depth;
        }

        int m_split_thickness_in_pixels;
        double m_split_depth;
    };
}

Renderer raytracer::rendering::split_depth(unsigned horizontal_resolution, unsigned vertical_resolution, raytracer::Sampler sampler, RayTracer ray_tracer, std::shared_ptr<util::Looper> looper, double split_thickness, double split_depth)
{
    return Renderer(std::make_shared<SplitDepthRenderer>(horizontal_resolution, vertical_resolution, sampler, ray_tracer, looper, split_thickness, split_depth));
}