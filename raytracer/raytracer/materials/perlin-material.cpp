#include "materials/perlin-material.h"
#include "math/functions/perlin.h"
#include "math/functions/functions.h"

using namespace raytracer;
using namespace raytracer::materials;
using namespace math;
using namespace math::functions;
using namespace imaging;


namespace
{
    Function<Point2D, const Point2D&> scale(double factor)
    {
        std::function<Point2D(const Point2D&)> lambda = [factor](const Point2D& p) -> Point2D {
            return Point2D(p.x * factor, p.y * factor);
        };

        return from_lambda(lambda);
    }

    Noise2D create_perlin2d_noise_function()
    {        
        auto p = perlin2d(15);
        auto p1 = p;
        auto p2 = (scale(2) >> p) / 2.0;
        auto p4 = (scale(4) >> p) / 4.0;
        auto p8 = (scale(8) >> p) / 8.0;

        return p1 + p2 + p4 + p8;
    }
}

raytracer::materials::_private_::PerlinMaterial2D::PerlinMaterial2D()
    : m_noise_function(create_perlin2d_noise_function())
{
    // NOP
}

MaterialProperties raytracer::materials::_private_::PerlinMaterial2D::at(const HitPosition& hp) const
{
    Point2D p = hp.uv;

    MaterialProperties properties;
    properties.ambient = colors::black();
    properties.diffuse = this->m_noise_function(p) * colors::white();
    properties.specular = colors::black();
    properties.specular_exponent = 0.0;
    properties.reflectivity = 0.0;

    return properties;
}

Material raytracer::materials::perlin2d()
{
    return Material(std::make_shared<_private_::PerlinMaterial2D>());
}