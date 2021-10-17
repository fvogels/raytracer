#include "renderers/group-renderer.h"
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
    class GroupRenderer : public raytracer::renderers::_private_::RendererBaseImplementation
    {
    public:
        GroupRenderer(
            unsigned horizontal_size,
            unsigned vertical_size,
            raytracer::Sampler sampler,
            RayTracer ray_tracer,
            tasks::TaskScheduler scheduler,
            const Color& background_color)
            : RendererBaseImplementation(horizontal_size, vertical_size, sampler, ray_tracer, scheduler)            
            , m_background_color(background_color)
        {
            // NOP
        }

        std::shared_ptr<imaging::Bitmap> render(const Scene& scene) const override
        {
            TIMED_FUNC(timer);

            // Create a [0,1] x [0,1] window.
            Rectangle2D window(Point2D(0, 1), Vector2D(1, 0), Vector2D(0, -1));

            // Divide this window in small rectangles (which represent pixels)
            Rasterizer window_rasterizer(window, m_horizontal_size, m_vertical_size);

            // Create a bitmap of the same size
            auto result = std::make_shared<Bitmap>(m_horizontal_size, m_vertical_size);
            Bitmap& bitmap = *result;

            // Repeat for each pixel
            for_each_pixel([&](Position2D pixel_coordinates) {
                // Determine the color of the pixel
                Color c = render_pixel(window_rasterizer, pixel_coordinates, scene);

                // Assign color to bitmap
                bitmap[pixel_coordinates] = c;
            });

            return result;
        }

        //std::shared_ptr<imaging::Bitmap> render(const Scene& scene) const
        //{
        //    Rectangle2D window(Point2D(0, 0), Vector2D(1, 0), Vector2D(0, 1));
        //    Rasterizer window_rasterizer(window, m_horizontal_size, m_vertical_size);
        //    auto result = std::make_shared<Bitmap>(m_horizontal_size, m_vertical_size);
        //    auto& bitmap = *result;
        //    bitmap.clear(m_background_color);

        //    for_each_pixel([&](Position2D pixel_coordinates) {
        //        assert(pixel_coordinates.x < m_horizontal_size);
        //        assert(pixel_coordinates.y < m_vertical_size);

        //        math::Rectangle2D pixel_rectangle = window_rasterizer[pixel_coordinates];
        //        auto color = colors::black();
        //        auto sample_count = 0;

        //        m_sampler->sample(pixel_rectangle, [&](const Point2D& p) {
        //            scene.camera->enumerate_rays(p, [&](const Ray& ray) {
        //                TraceResult tr = m_ray_tracer->trace(scene, ray);
        //                const auto group_id = tr.group_id;
        //                color += determine_group_color(group_id);
        //                sample_count++;
        //            });
        //        });

        //        assert(sample_count != 0);

        //        bitmap[pixel_coordinates] = color / sample_count;
        //    });
        //    
        //    return result;
        //}

    private:
        Color render_pixel(const math::Rasterizer& window_rasterizer, const Position2D& position, const Scene& scene) const
        {
            math::Rectangle2D pixel_rectangle = window_rasterizer[position];
            imaging::Color c = imaging::colors::black();
            unsigned sample_count = 0;
            auto samples = m_sampler->sample(pixel_rectangle);

            m_sampler->sample(pixel_rectangle, [this, &c, &sample_count, &scene](const Point2D& sample_position) {
                scene.camera->enumerate_rays(sample_position, [this, &c, &sample_count, &scene](const Ray& ray) {
                    const auto group_id = m_ray_tracer->trace(scene, ray).group_id;
                    c += determine_group_color(group_id);
                    ++sample_count;
                });
            });

            assert(sample_count > 0);

            return c / sample_count;
        }

        Color determine_group_color(unsigned group_id) const
        {
            if (group_id == MISSING_ID)
            {
                return m_background_color;
            }

            switch (group_id % 6)
            {
            case 0:
                return colors::red();
            case 1:
                return colors::green();
            case 2:
                return colors::blue();
            case 3:
                return colors::magenta();
            case 4:
                return colors::yellow();
            default:
                return colors::cyan();
            }
        }

        Color m_background_color;
    };
}

Renderer raytracer::renderers::group(unsigned horizontal_size, unsigned vertical_size, raytracer::Sampler sampler, RayTracer ray_tracer, tasks::TaskScheduler scheduler, const Color& background_color)
{
    return Renderer(std::make_shared<GroupRenderer>(horizontal_size, vertical_size, sampler, ray_tracer, scheduler, background_color));
}
