#include "lights/conical-light.h"
#include <assert.h>

using namespace math;
using namespace raytracer;
using namespace imaging;


raytracer::ConicalLight::ConicalLight(const math::Point3D& position, const math::Vector3D& direction, math::Angle angle, const imaging::color& c)
    : PointLight(position), m_direction(direction), m_min_cos(cos(angle)), m_color(c)
{
    assert(direction.is_unit());
}

LightRay raytracer::ConicalLight::cast_lightray_to(const math::Point3D& p) const
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
