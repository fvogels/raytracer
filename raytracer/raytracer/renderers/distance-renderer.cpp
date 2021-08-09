#include "renderers/distance-renderer.h"
#include "renderers/renderer-base.h"
#include "data-structures/grid.h"
#include "easylogging++.h"
#include <vector>
#include <limits>

using namespace imaging;
using namespace math;
using namespace raytracer;
using namespace raytracer::renderers;


namespace
{
    class DistanceRenderer : public raytracer::renderers::_private_::RendererBaseImplementation
    {
    private:
        Point3D m_eye;
        double m_factor;
        double m_exponent;

    public:
        DistanceRenderer(
            unsigned horizontal_size,
            unsigned vertical_size,
            raytracer::Sampler sampler,
            RayTracer ray_tracer,
            tasks::TaskScheduler scheduler,
            const Point3D& eye,
            double factor,
            double exponent) : RendererBaseImplementation(horizontal_size, vertical_size, sampler, ray_tracer, scheduler)
                             , m_eye(eye)
                             , m_factor(factor)
                             , m_exponent(exponent)
        {
            // NOP
        }

        std::shared_ptr<imaging::Bitmap> render(const Scene& scene) const
        {
            Rectangle2D window(Point2D(0, 0), Vector2D(1, 0), Vector2D(0, 1));
            Rasterizer window_rasterizer(window, m_horizontal_size, m_vertical_size);
            auto result = std::make_shared<Bitmap>(m_horizontal_size, m_vertical_size);
            Bitmap& bitmap = *result;
            bitmap.clear(colors::white());

            for_each_pixel([&](Position2D pixel_coordinates) {
                assert(pixel_coordinates.x < m_horizontal_size);
                assert(pixel_coordinates.y < m_vertical_size);

                Position2D bitmap_coordinates(pixel_coordinates.x, bitmap.height() - pixel_coordinates.y - 1);
                auto pixel_rectangle = window_rasterizer[pixel_coordinates];
                double closest_distance = std::numeric_limits<double>::infinity();

                m_sampler->sample(pixel_rectangle, [&](const Point2D& p) {
                    scene.camera->enumerate_rays(p, [&](const Ray& ray) {
                        auto tr = m_ray_tracer->trace(scene, ray);
                        auto dist = distance(tr.hit_position(), m_eye);

                        closest_distance = std::min(closest_distance, dist);
                    });
                });

                auto gray_level = std::pow(1 - std::min(closest_distance * m_factor, 1.0), m_exponent);
                Color color(gray_level, gray_level, gray_level);

                bitmap[bitmap_coordinates] = color;
            });

            return result;
        }
    };
}

Renderer raytracer::renderers::distance(unsigned horizontal_size, unsigned vertical_size, raytracer::Sampler sampler, RayTracer ray_tracer, tasks::TaskScheduler scheduler, const Point3D& eye, double factor, double exponent)
{
    return Renderer(std::make_shared<DistanceRenderer>(horizontal_size, vertical_size, sampler, ray_tracer, scheduler, eye, factor, exponent));
}
