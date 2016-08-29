#include "materials/worley-material.h"
#include "math/functions/worley.h"
#include <cmath>

using namespace raytracer;
using namespace raytracer::materials;
using namespace math;
using namespace imaging;


namespace
{
    class WorleyMaterial2D : public raytracer::materials::_private_::MaterialImplementation
    {
    public:
        WorleyMaterial2D(unsigned density, double factor, double power)
            : m_noise_function(math::functions::worley2d(density)), m_factor(factor), m_power(power)
        {
            // NOP
        }

        MaterialProperties at(const HitPosition& hp) const override
        {
            Point2D p = hp.uv;
            double brightness = m_factor * pow(this->m_noise_function(p), m_power);
            MaterialProperties properties(colors::black(), brightness * colors::white(), colors::black(), 0.0, 0.0, 0.0, 0.0);

            return properties;
        }

    private:
        math::functions::Noise2D m_noise_function;
        double m_factor;
        double m_power;
    };

    class WorleyMaterial3D : public raytracer::materials::_private_::MaterialImplementation
    {
    public:
        WorleyMaterial3D(unsigned density, double factor, double power)
            : m_noise_function(math::functions::worley3d(density)), m_factor(factor), m_power(power)
        {
            // NOP
        }

        MaterialProperties at(const HitPosition& hp) const override
        {
            Point3D p = hp.xyz;
            double brightness = m_factor * pow(this->m_noise_function(p), m_power);
            MaterialProperties properties(colors::black(), brightness * colors::white(), colors::black(), 0.0, 0.0, 0.0, 0.0);

            return properties;
        }

    private:
        math::functions::Noise3D m_noise_function;
        double m_factor;
        double m_power;
    };
}

Material raytracer::materials::worley2d(unsigned density, double factor, double power)
{
    return Material(std::make_shared<WorleyMaterial2D>(density, factor, power));
}

Material raytracer::materials::worley3d(unsigned density, double factor, double power)
{
    return Material(std::make_shared<WorleyMaterial3D>(density, factor, power));
}
