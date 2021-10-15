#include "renderers/cartoon-renderer.h"
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
    class CartoonRenderer : public raytracer::renderers::_private_::RendererBaseImplementation
    {
    public:
        CartoonRenderer(
            unsigned horizontal_size,
            unsigned vertical_size,
            raytracer::Sampler sampler,
            RayTracer ray_tracer,
            tasks::TaskScheduler scheduler,
            unsigned shade_count)
            : RendererBaseImplementation(horizontal_size, vertical_size, sampler, ray_tracer, scheduler)
            , m_shade_count(shade_count)
        {
            // NOP
        }

        std::shared_ptr<imaging::Bitmap> render(const Scene& scene) const override
        {
            TIMED_FUNC(timer);

            auto result = std::make_shared<Bitmap>(m_horizontal_size, m_vertical_size);
            Bitmap& bitmap = *result;
            Rectangle2D window(Point2D(0, 1), Vector2D(1, 0), Vector2D(0, -1));
            Rasterizer window_rasterizer(window, bitmap.width(), bitmap.height());

            for_each_pixel([&](Position2D pixel_coordinates) {
                math::Rectangle2D pixel_rectangle = window_rasterizer[pixel_coordinates];
                imaging::Color c = imaging::colors::black();
                unsigned sample_count = 0;

                m_sampler->sample(pixel_rectangle, [&](const Point2D& p) {
                    scene.camera->enumerate_rays(p, [&](const Ray& ray) {
                        TraceResult tr = m_ray_tracer->trace(scene, ray);
                        c += tr.color;
                        ++sample_count;
                    });
                });

                c /= sample_count;

                bitmap[pixel_coordinates] = c.quantized(m_shade_count);
            });

            return result;
        }

    private:
        unsigned m_shade_count;
    };
}

Renderer raytracer::renderers::cartoon(unsigned horizontal_size, unsigned vertical_size, raytracer::Sampler sampler, RayTracer ray_tracer, tasks::TaskScheduler scheduler, unsigned shade_count)
{
    return Renderer(std::make_shared<CartoonRenderer>(horizontal_size, vertical_size, sampler, ray_tracer, scheduler, shade_count));
}
