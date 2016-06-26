#include "lights/point-light.h"

using namespace math;
using namespace raytracer;
using namespace imaging;


raytracer::lights::_private_::PointLight::PointLight(const math::Point3D& position)
    : m_position(position) { }

std::vector<LightRay> raytracer::lights::_private_::PointLight::lightrays_to(const math::Point3D& p) const
{
    auto result = this->cast_lightray_to(p);

    if (result.color != colors::black())
    {
        return std::vector<LightRay> { result };
    }
    else
    {
        return std::vector<LightRay>();
    }
}
