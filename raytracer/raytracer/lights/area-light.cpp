#include "lights/area-light.h"
#include <assert.h>

using namespace math;
using namespace raytracer;
using namespace imaging;


raytracer::lights::_private_::AreaLight::AreaLight(const math::Rectangle3D& area, Sampler sampler, const imaging::color& color)
    : m_area(area), m_sampler(sampler), m_color(color)
{
    assert(sampler);
}

std::vector<LightRay> raytracer::lights::_private_::AreaLight::lightrays_to(const math::Point3D& illuminated_point) const
{
    std::vector<LightRay> light_rays;
    unsigned count = 0;

    Rectangle2D rect_2d(Point2D(0, 0), Vector2D(1, 0), Vector2D(0, 1));
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

LightSource raytracer::lights::area(const math::Rectangle3D& area, raytracer::Sampler sampler, const imaging::color& color)
{
    return LightSource(std::make_shared<raytracer::lights::_private_::AreaLight>(area, sampler, color));
}