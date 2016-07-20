#include "rendering/single-threaded-renderer.h"
#include <sstream>
#include "easylogging++.h"

using namespace math;
using namespace imaging;
using namespace raytracer;
using namespace raytracer::rendering;


imaging::Bitmap raytracer::rendering::_private_::SingleThreadedRenderer::render(const Scene& scene) const
{
    Bitmap bitmap(m_horizontal_resolution, m_vertical_resolution);
    Rectangle2D window(point(0, 0), vector(1, 0), vector(0, 1));
    Rasterizer window_rasterizer(window, bitmap.width(), bitmap.height());

    for (int j = 0; j != bitmap.height(); ++j)
    {
        int y = bitmap.height() - j - 1;

        for (int i = 0; i != bitmap.width(); ++i)
        {
            int x = i;

            color c = render_pixel(window_rasterizer, x, y, scene);

            bitmap[position(i, j)] = c;
        }
    }

    return bitmap;
}

Renderer raytracer::rendering::single_threaded(unsigned horizontal_resolution, unsigned vertical_resolution, raytracer::Sampler sampler, RayTracer ray_tracer)
{
    return Renderer(std::make_shared<_private_::SingleThreadedRenderer>(horizontal_resolution, vertical_resolution, sampler, ray_tracer));
}