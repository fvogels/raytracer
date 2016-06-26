#include "cone-light.h"
#include <assert.h>

using namespace math;
using namespace raytracer;


raytracer::ConeLight::ConeLight(const math::Point3D& position, const math::Vector3D& direction, math::Angle angle, const imaging::color& c)
    : m_position(position), m_direction(direction), m_min_cos(cos(angle)), m_color(c)
{
    assert(direction.is_unit());
}

std::vector<LightRay> raytracer::ConeLight::lightrays_to(const math::Point3D& p) const
{
    Ray ray(m_position, p);
    double intensity = ray.direction.normalized().dot(m_direction);

    if (intensity > m_min_cos)
    {
        return std::vector<LightRay> { LightRay(ray, m_color * intensity) };
    }
    else
    {
        return std::vector<LightRay>();
    }
}
