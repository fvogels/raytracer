#include "lights/omnidirectional-point-light.h"

using namespace math;
using namespace raytracer;


raytracer::OmnidirectionalPointLight::OmnidirectionalPointLight(const math::Point3D& position, const imaging::color& c)
    : PointLight(position), m_color(c) { }

LightRay raytracer::OmnidirectionalPointLight::cast_lightray_to(const math::Point3D& p) const
{
    math::Ray ray(position, p);

    return LightRay(ray, m_color);
}