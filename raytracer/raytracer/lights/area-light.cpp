#include "lights/area-light.h"
#include <assert.h>

using namespace math;
using namespace raytracer;
using namespace imaging;


namespace
{
    class AreaLight : public raytracer::lights::_private_::LightSourceImplementation
    {
    public:
        AreaLight(const math::Rectangle3D& area, Sampler sampler, const imaging::Color& color)
            : m_area(area), m_sampler(sampler), m_color(color)
        {
            assert(sampler);
        }

        std::vector<LightRay> lightrays_to(const math::Point3D& illuminated_point) const override
        {
            std::vector<LightRay> light_rays;
            unsigned count = 0;

            Rectangle2D rect_2d(point(0, 0), vector(1, 0), vector(0, 1));
            m_sampler->sample(rect_2d, [this, &count, &illuminated_point, &light_rays](const Point2D& p2d) {
                Point3D p3d = m_area.project(p2d);
                Ray ray(p3d, illuminated_point);
                light_rays.push_back(LightRay(ray, m_color));
                ++count;
            });

            for (auto& light_ray : light_rays)
            {
                light_ray.color /= count;
            }

            return light_rays;
        }

    private:
        math::Rectangle3D m_area;
        raytracer::Sampler m_sampler;
        imaging::Color m_color;
    };
}

LightSource raytracer::lights::area(const math::Rectangle3D& area, raytracer::Sampler sampler, const imaging::Color& color)
{
    return LightSource(std::make_shared<AreaLight>(area, sampler, color));
}