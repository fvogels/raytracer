#include "lights/spot-light.h"
#include <assert.h>

using namespace math;
using namespace raytracer;
using namespace imaging;

namespace
{
    class SpotLight : public raytracer::lights::_private_::PointLightImplementation
    {
    public:
        SpotLight(const math::Point3D& position, const math::Vector3D& direction, math::Angle angle, const imaging::Color& color)
            : PointLightImplementation(position), m_direction(direction), m_min_cos(cos(angle)), m_color(color)
        {
            assert(direction.is_unit());
        }

    protected:
        LightRay cast_lightray_to(const math::Point3D& p) const override
        {
            Ray ray(m_position, p);
            double intensity = ray.direction.normalized().dot(m_direction);

            if (intensity > m_min_cos)
            {
                return LightRay(ray, m_color);
            }
            else
            {
                return LightRay(ray, colors::black());
            }
        }

    private:
        math::Vector3D m_direction;
        double m_min_cos;
        imaging::Color m_color;
    };
}

LightSource raytracer::lights::spot(const math::Point3D& position, const math::Vector3D& direction, math::Angle angle, const imaging::Color& color)
{
    return LightSource(std::make_shared<SpotLight>(position, direction, angle, color));
}

LightSource raytracer::lights::spot(const math::Point3D& position, const math::Point3D& pointed_at, math::Angle angle, const imaging::Color& color)
{
    return LightSource(std::make_shared<SpotLight>(position, (pointed_at - position).normalized(), angle, color));
}