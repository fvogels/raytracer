#include "lights/anisotropic-light.h"
#include "math/interval.h"
#include "math/coordinate-systems.h"
#include <assert.h>

using namespace math;
using namespace raytracer;
using namespace imaging;

namespace
{
    class AnisotropicLight : public lights::_private_::PointLightImplementation
    {
    public:
        AnisotropicLight(const math::Point3D& position, const math::Vector3D& direction, const math::Vector3D& up, math::Function<imaging::Color(Angle, Angle)> light_function)
            : lights::_private_::PointLightImplementation(position), m_direction(direction), m_right(direction.cross(up)), m_up(m_right.cross(m_direction)), m_light_function(light_function)
        {
            assert(m_direction.is_unit());
            assert(m_up.is_unit());
            assert(m_right.is_unit());
            assert(m_direction.is_perpendicular_on(m_up));
            assert(m_direction.is_perpendicular_on(m_right));
            assert(m_right.is_perpendicular_on(m_up));
            assert(light_function);
        }

    protected:
        LightRay cast_lightray_to(const math::Point3D& p) const
        {
            assert(m_direction.is_unit());

            Ray ray(m_position, p);
            auto ray_direction = ray.direction.normalized();

            double x = ray_direction.dot(m_right);
            double y = ray_direction.dot(m_direction);
            double z = ray_direction.dot(m_up);

            assert(Interval<double>(-1, 1).contains(x));
            assert(Interval<double>(-1, 1).contains(y));
            assert(Interval<double>(-1, 1).contains(z));
            assert(x * m_right + y * m_direction + z * m_up == approx(ray_direction));

            Cartesian3D cartesian{ x,y,z };
            Spherical spherical = convert_coordinates<Spherical>(cartesian);
            Color color = m_light_function(spherical.azimuth, spherical.elevation);

            return LightRay(ray, color);
        }

    private:
        math::Vector3D m_direction;
        math::Vector3D m_right;
        math::Vector3D m_up; // Must appear last! Important for initialization order
        math::Function<imaging::Color(Angle, Angle)> m_light_function;
    };
}


LightSource raytracer::lights::anisotropic(const math::Point3D& position, const math::Vector3D& direction, math::Function<imaging::Color(Angle)> light_function)
{
    assert(direction.is_unit());

    std::function<Color(Angle, Angle)> lambda = [=](Angle azimuth, Angle elevation) {
        return light_function(elevation);
    };

    Vector3D up(0, -direction.z(), direction.y());
    up.normalize();

    assert(direction.is_perpendicular_on(up));
    assert(up.is_unit());

    return LightSource(std::make_shared<AnisotropicLight>(position, direction, up, from_lambda(lambda)));
}

LightSource raytracer::lights::anisotropic(const math::Point3D& position, const math::Point3D& pointed_at, math::Function<imaging::Color(Angle)> light_function)
{
    auto direction = (pointed_at - position).normalized();

    return anisotropic(position, direction, light_function);
}

//LightSource raytracer::lights::anisotropic_monochromatic(const math::Point3D& position, const math::Vector3D& direction, math::Function<double(double)> brightness_function, imaging::Color color)
//{
//    std::Function<Color(double(double))> lambda = [=](double azimuth, double elevation) {
//        return color * brightness_function(elevation);
//    };
//
//    return LightSource(std::make_shared<AnisotropicLight>(position, direction, from_lambda(lambda)));
//}
//
//LightSource raytracer::lights::anisotropic_monochromatic(const math::Point3D& position, const math::Point3D& pointed_at, math::Function<double(double)> brightness_function, imaging::Color color)
//{
//    return anisotropic_monochromatic(position, (pointed_at - position).normalized(), brightness_function, color);
//}
