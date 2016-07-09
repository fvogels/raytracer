#include "lights/spot-light.h"
#include <assert.h>

using namespace math;
using namespace raytracer;
using namespace imaging;


raytracer::lights::_private_::SpotLight::SpotLight(const math::Point3D& position, const math::Vector3D& direction, math::Angle angle, const imaging::color& color)
    : PointLightImplementation(position), m_direction(direction), m_min_cos(cos(angle)), m_color(color)
{
    assert(direction.is_unit());
}

LightRay raytracer::lights::_private_::SpotLight::cast_lightray_to(const math::Point3D& p) const
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

lights::LightSource raytracer::lights::spot(const math::Point3D& position, const math::Vector3D& direction, math::Angle angle, const imaging::color& color)
{
    return LightSource(std::make_shared<raytracer::lights::_private_::SpotLight>(position, direction, angle, color));
}

lights::LightSource raytracer::lights::spot(const math::Point3D& position, const math::Point3D& pointed_at, math::Angle angle, const imaging::color& color)
{
    return LightSource(std::make_shared<raytracer::lights::_private_::SpotLight>(position, (pointed_at - position).normalized(), angle, color));
}