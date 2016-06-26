#include "lights/point-light.h"

using namespace math;
using namespace raytracer;


raytracer::PointLight::PointLight(const math::Point3D& position, const imaging::color& c)
        : position(position), m_color(c) { }

std::vector<LightRay> raytracer::PointLight::lightrays_to(const math::Point3D& p) const
{
    math::Ray ray(position, p);

    return std::vector<LightRay> { LightRay(ray, m_color) };
}
