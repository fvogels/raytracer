#include "materials/material.h"
#include "materials/materials.h"
#include "materials/uniform-material.h"
#include "math/function.h"
#include "math/functions.h"
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
    class MultiMaterial : public materials::_private_::MaterialImplementation
    {
    public:
        MultiMaterial(math::Function<Material(const Point2D&)> function)
            : m_function(function) { }

        MaterialProperties at(const HitPosition& hp) const override
        {
            return m_function(hp.uv)->at(hp);
        }

    private:
        math::Function<Material(const Point2D&)> m_function;
    };
}

Material raytracer::materials::pattern2d(math::Function<bool(const Point2D&)> pattern, Material m1, Material m2)
{
    auto bool_mapper = math::functions::bool_mapper(m1, m2);

    return Material(std::make_shared<MultiMaterial>(pattern >> bool_mapper));
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

Material raytracer::materials::polka(double radius, Material m1, Material m2)
{
    return pattern2d(math::functions::polka(radius), m1, m2);
}

Material raytracer::materials::polka(double radius1, double radius2, Material m1, Material m2)
{
    return pattern2d(math::functions::polka(radius1, radius2), m1, m2);
}

Material raytracer::materials::dalmatian(unsigned density, Material m1, Material m2)
{
    return pattern2d(math::functions::dalmatian(density, 5461), m1, m2);
}
