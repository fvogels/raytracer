#include "lights/omnidirectional-point-light.h"

using namespace math;
using namespace raytracer;


raytracer::lights::_private_::OmnidirectionalPointLight::OmnidirectionalPointLight(const math::Point3D& position, const imaging::Color& color)
    : PointLightImplementation(position), m_color(color) { }

LightRay raytracer::lights::_private_::OmnidirectionalPointLight::cast_lightray_to(const math::Point3D& p) const
{
    math::Ray ray(m_position, p);

    return LightRay(ray, m_color);
}

LightSource raytracer::lights::omnidirectional(const math::Point3D& position, const imaging::Color& color)
{
    return LightSource(std::make_shared<raytracer::lights::_private_::OmnidirectionalPointLight>(position, color));
}
