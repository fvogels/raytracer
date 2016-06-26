#include "materials/material.h"
#include "materials/materials.h"
#include "materials/uniform-material.h"
#include "math/function.h"
#include "math/functions/functions.h"
#include "math/functions/patterns.h"
#include "math/functions/noise.h"
#include "math/functions/bool-mapper.h"
#include "imaging/color-mapper.h"

using namespace math;
using namespace raytracer;
using namespace raytracer::materials;
using namespace imaging;


namespace
{
    class MultiMaterial : public MaterialImplementation
    {
    public:
        MultiMaterial(math::Function<Material, const Point2D&> function)
            : m_function(function) { }

        MaterialProperties at(const HitPosition& hp) const override
        {
            return m_function(hp.uv)->at(hp);
        }

    private:
        math::Function<Material, const Point2D&> m_function;
    };
}

//Material raytracer::materials::worley(const color& c1, const color& c2)
//{
//    auto color_mapper = color_mapping::grayscale();
//    math::Function<double, const Point2D&> texture = math::functions::worley_noise2d();
//
//    return Material(std::make_shared<MultiMaterial>(texture >> color_mapper));
//}

Material raytracer::materials::pattern2d(math::Function<bool, const Point2D&> pattern, Material m1, Material m2)
{
    auto bool_mapper = math::functions::bool_mapper(m1, m2);

    return Material(std::make_shared<MultiMaterial>(pattern >> bool_mapper));
}

Material raytracer::materials::uniform(const color& diffuse, const color& specular, double specular_exponent, double reflectivity)
{
    return Material(std::make_shared<UniformMaterial>(diffuse, specular, specular_exponent, reflectivity));
}

Material raytracer::materials::checkered(Material m1, Material m2)
{
    return pattern2d(math::functions::checkered(), m1, m2);
}

Material raytracer::materials::horizontal_lines(double thickness, Material m1, Material m2)
{
    return pattern2d(math::functions::horizontal_lines(thickness), m1, m2);
}

Material raytracer::materials::vertical_lines(double thickness, Material m1, Material m2)
{
    return pattern2d(math::functions::vertical_lines(thickness), m1, m2);
}

Material raytracer::materials::grid(double thickness, Material m1, Material m2)
{
    return pattern2d(math::functions::grid(thickness), m1, m2);
}
