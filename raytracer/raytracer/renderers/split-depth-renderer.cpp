#include "renderers/split-depth-renderer.h"
#include "easylogging++.h"
#include <limits>
#include <cmath>

using namespace imaging;
using namespace math;
using namespace raytracer;
using namespace raytracer::renderers;


namespace
{
    class SplitDepthRenderer : public raytracer::renderers::_private_::RendererImplementation
    {
    public:
        SplitDepthRenderer(unsigned horizontal_size, unsigned vertical_size, raytracer::Sampler sampler, RayTracer ray_tracer, tasks::TaskScheduler scheduler, double split_thickness, const math::Plane& split_plane)
            : RendererImplementation(horizontal_size, vertical_size, sampler, ray_tracer, scheduler), m_split_thickness_in_pixels(int(split_thickness * horizontal_size)), m_split_plane(split_plane)
        {
            // NOP
        }

        std::shared_ptr<imaging::Bitmap> render(const Scene& scene) const override
        {
            TIMED_FUNC(timer);

            Rectangle2D window(Point2D(0, 0), Vector2D(1, 0), Vector2D(0, 1));
            Rasterizer window_rasterizer(window, m_horizontal_size, m_vertical_size);
            auto result = std::make_shared<Bitmap>(m_horizontal_size, m_vertical_size);
            Bitmap& bitmap = *result;

            for_each_pixel([&](Position2D pixel_coordinates) {
                Position2D bitmap_coordinates(pixel_coordinates.x, bitmap.height() - pixel_coordinates.y - 1);
                bool on_split = is_on_split(pixel_coordinates);

                math::Rectangle2D pixel_rectangle = window_rasterizer[pixel_coordinates];
                imaging::Color color = imaging::colors::black();
                int sample_count = 0;

                m_sampler->sample(pixel_rectangle, [this, on_split, &color, &sample_count, &scene](const Point2D& p) {
                    scene.camera->enumerate_rays(p, [this, on_split, &color, &sample_count, &scene](const Ray& ray) {
                        auto trace_result = m_ray_tracer->trace(scene, ray);

                        if (!on_split || is_in_front_of_split_plane(trace_result.hit_position()))
                        {
                            color += trace_result.color;
                        }
                        else
                        {
                            color += colors::white();
                        }

                        ++sample_count;
                    });
                });

                color /= sample_count;

                bitmap[bitmap_coordinates] = color;
            });

            return result;
        }

    private:
        bool is_on_split(const Position2D& pixel_coordinates) const
        {
            return abs(int(pixel_coordinates.x) - int(m_horizontal_size / 3)) < m_split_thickness_in_pixels / 2 ||
                abs(int(pixel_coordinates.x) - int(2 * m_horizontal_size / 3)) < m_split_thickness_in_pixels / 2;
        }

        bool is_in_front_of_split_plane(const Point3D& point) const
        {
            return lies_in_front_of(m_split_plane, point);
        }

        int m_split_thickness_in_pixels;
        math::Plane m_split_plane;
    };
}

Renderer raytracer::renderers::split_depth(unsigned horizontal_size, unsigned vertical_size, raytracer::Sampler sampler, RayTracer ray_tracer, tasks::TaskScheduler scheduler, double split_thickness, const math::Plane& split_plane)
{
    return Renderer(std::make_shared<SplitDepthRenderer>(horizontal_size, vertical_size, sampler, ray_tracer, scheduler, split_thickness, split_plane));
}

Renderer raytracer::renderers::split_depth(unsigned horizontal_size, unsigned vertical_size, raytracer::Sampler sampler, RayTracer ray_tracer, tasks::TaskScheduler scheduler, double split_thickness, const Point3D& eye, const Point3D& look_at)
{
    auto split_plane = math::Plane::from_point_and_normal(look_at, (eye - look_at).normalized());

    return split_depth(horizontal_size, vertical_size, sampler, ray_tracer, scheduler, split_thickness, split_plane);
}
