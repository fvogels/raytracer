#include "lights/directional-light.h"
#include <assert.h>

using namespace math;
using namespace raytracer;
using namespace imaging;


namespace
{
    class DirectionalLight : public raytracer::lights::_private_::LightSourceImplementation
    {
    public:
        DirectionalLight(const math::Vector3D& direction, const imaging::Color& color)
            : m_direction(direction), m_color(color)
        {
            assert(direction.is_unit());
        }

        std::vector<LightRay> lightrays_to(const math::Point3D& p) const override
        {
            Ray ray(p - m_direction * 1000, p);
            LightRay light_ray(ray, m_color);

            return std::vector<LightRay> { light_ray };
        }

    private:
        math::Vector3D m_direction;
        imaging::Color m_color;
    };
}

LightSource raytracer::lights::directional(const math::Vector3D& direction, const imaging::Color& color)
{
    return LightSource(std::make_shared<DirectionalLight>(direction, color));
}