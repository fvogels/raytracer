#include "lights/conical-light.h"
#include <assert.h>

using namespace math;
using namespace raytracer;
using namespace imaging;


raytracer::lights::_private_::ConicalLight::ConicalLight(const math::Point3D& position, const math::Vector3D& direction, math::Angle angle, const imaging::color& color)
    : PointLight(position), m_direction(direction), m_min_cos(cos(angle)), m_color(color)
{
    assert(direction.is_unit());
}

LightRay raytracer::lights::_private_::ConicalLight::cast_lightray_to(const math::Point3D& p) const
{
    Ray ray(m_position, p);
    double intensity = ray.direction.normalized().dot(m_direction);

    if (intensity > m_min_cos)
    {
        return LightRay(ray, m_color * intensity);
    }
    else
    {
        return LightRay(ray, colors::black());
    }
}

std::shared_ptr<lights::LightSource> raytracer::lights::conical(const math::Point3D& position, const math::Vector3D& direction, math::Angle angle, const imaging::color& color)
{
    return std::make_shared<raytracer::lights::_private_::ConicalLight>(position, direction, angle, color);
}