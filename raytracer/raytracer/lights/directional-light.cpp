#include "lights/directional-light.h"
#include <assert.h>

using namespace math;
using namespace raytracer;
using namespace imaging;


raytracer::lights::_private_::DirectionalLight::DirectionalLight(const math::Vector3D& direction, const imaging::color& color)
    : m_direction(direction), m_color(color)
{
    assert(direction.is_unit());
}

std::vector<LightRay> raytracer::lights::_private_::DirectionalLight::lightrays_to(const math::Point3D& p) const
{
    Ray ray(p - m_direction * 1000, m_direction * 1000);
    LightRay light_ray(ray, m_color);

    return std::vector<LightRay> { light_ray };
}

LightSource raytracer::lights::directional(const math::Vector3D& direction, const imaging::color& color)
{
    return LightSource(std::make_shared<raytracer::lights::_private_::DirectionalLight>(direction, color));
}