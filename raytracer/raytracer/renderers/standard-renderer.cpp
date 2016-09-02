#include "renderers/standard-renderer.h"
#include "easylogging++.h"

using namespace imaging;
using namespace math;
using namespace raytracer;
using namespace raytracer::renderers;


namespace
{
    class StandardRenderer : public raytracer::renderers::_private_::RendererImplementation
    {
    public:
        StandardRenderer(unsigned horizontal_size, unsigned vertical_size, raytracer::Sampler sampler, RayTracer ray_tracer, std::shared_ptr<loopers::Looper> looper)
            : RendererImplementation(horizontal_size, vertical_size, sampler, ray_tracer, looper)
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

            for_each_pixel([&](Position pixel_coordinates) {
                Position bitmap_coordinates(pixel_coordinates.x, bitmap.height() - pixel_coordinates.y - 1);
                Color c = render_pixel(window_rasterizer, pixel_coordinates, scene);

                bitmap[bitmap_coordinates] = c;
            });

            return result;
        }

    private:
        Color render_pixel(const math::Rasterizer& window_rasterizer, const Position& position, const Scene& scene) const
        {
            math::Rectangle2D pixel_rectangle = window_rasterizer[position];
            imaging::Color c = imaging::colors::black();
            int sample_count = 0;

            m_sampler->sample(pixel_rectangle, [this, &c, &sample_count, &scene](const Point2D& p) {
                scene.camera->enumerate_rays(p, [this, &c, &sample_count, &scene](const Ray& ray) {
                    c += m_ray_tracer->trace(scene, ray).color;
                    ++sample_count;
                });
            });

            return c / sample_count;
        }

        unsigned m_thread_count;
    };
}

Renderer raytracer::renderers::standard(unsigned horizontal_size, unsigned vertical_size, raytracer::Sampler sampler, RayTracer ray_tracer, std::shared_ptr<loopers::Looper> looper)
{
    return Renderer(std::make_shared<StandardRenderer>(horizontal_size, vertical_size, sampler, ray_tracer, looper));
}