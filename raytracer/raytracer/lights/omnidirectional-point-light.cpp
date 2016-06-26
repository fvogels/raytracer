#include "lights/omnidirectional-point-light.h"

using namespace math;
using namespace raytracer;


raytracer::lights::_private_::OmnidirectionalPointLight::OmnidirectionalPointLight(const math::Point3D& position, const imaging::color& color)
    : PointLight(position), m_color(color) { }

LightRay raytracer::lights::_private_::OmnidirectionalPointLight::cast_lightray_to(const math::Point3D& p) const
{
    math::Ray ray(position, p);

    return LightRay(ray, m_color);
}

std::shared_ptr<lights::LightSource> raytracer::lights::omnidirectional(const math::Point3D& position, const imaging::color& color)
{
    return std::make_shared<raytracer::lights::_private_::OmnidirectionalPointLight>(position, color);
}