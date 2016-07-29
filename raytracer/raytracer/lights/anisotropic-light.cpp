#include "lights/anisotropic-light.h"
#include "math/interval.h"
#include <assert.h>

using namespace math;
using namespace raytracer;
using namespace imaging;

namespace
{
    class AnisotropicLight : public lights::_private_::PointLightImplementation
    {
    public:
        AnisotropicLight(const math::Point3D& position, const math::Vector3D& direction, math::Function<imaging::Color, double> light_function)
            : lights::_private_::PointLightImplementation(position), m_direction(direction), m_light_function(light_function)
        {
            assert(direction.is_unit());
            assert(light_function);
        }

    protected:
        LightRay cast_lightray_to(const math::Point3D& p) const
        {
            assert(m_direction.is_unit());

            Ray ray(m_position, p);
            double cos = ray.direction.normalized().dot(m_direction);

            assert(Interval<double>(-1, 1).contains(cos));

            Color color = m_light_function(cos);

            return LightRay(ray, color);
        }

    private:
        math::Vector3D m_direction;
        math::Function<imaging::Color, double> m_light_function;
    };
}


LightSource raytracer::lights::anisotropic(const math::Point3D& position, const math::Vector3D& direction,  math::Function<imaging::Color, double> light_function)
{
    return LightSource(std::make_shared<AnisotropicLight>(position, direction, light_function));
}

LightSource raytracer::lights::anisotropic(const math::Point3D& position, const math::Point3D& pointed_at,  math::Function<imaging::Color, double> light_function)
{
    return LightSource(std::make_shared<AnisotropicLight>(position, (pointed_at - position).normalized(), light_function));
}

LightSource raytracer::lights::anisotropic_monochromatic(const math::Point3D& position, const math::Vector3D& direction, math::Function<double, double> brightness_function, imaging::Color color)
{
    std::function<Color(double)> lambda = [=](double cos) {
        return color * brightness_function(cos);
    };

    return LightSource(std::make_shared<AnisotropicLight>(position, direction, from_lambda(lambda)));
}

LightSource raytracer::lights::anisotropic_monochromatic(const math::Point3D& position, const math::Point3D& pointed_at, math::Function<double, double> brightness_function, imaging::Color color)
{
    return anisotropic_monochromatic(position, (pointed_at - position).normalized(), brightness_function, color);
}