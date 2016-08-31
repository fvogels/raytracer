#include "materials/worley-material.h"
#include "math/functions/worley.h"
#include <cmath>

using namespace raytracer;
using namespace raytracer::materials;
using namespace math;
using namespace imaging;


namespace
{
    class WorleyMaterial2D : public raytracer::materials::_private_::Material2DImplementation
    {
    public:
        WorleyMaterial2D(unsigned density, double factor, double power)
            : m_noise_function(math::functions::worley2d(density)), m_factor(factor), m_power(power)
        {
            // NOP
        }

    protected:
        MaterialProperties at(const Point2D& p) const override
        {
            double brightness = m_factor * pow(this->m_noise_function(p), m_power);
            MaterialProperties properties(colors::black(), brightness * colors::white(), colors::black(), 0.0, 0.0, 0.0, 0.0);

            return properties;
        }

    private:
        math::functions::Noise2D m_noise_function;
        double m_factor;
        double m_power;
    };

    class WorleyMaterial3D : public raytracer::materials::_private_::Material3DImplementation
    {
    public:
        WorleyMaterial3D(unsigned density, double factor, double power)
            : m_noise_function(math::functions::worley3d(density)), m_factor(factor), m_power(power)
        {
            // NOP
        }

    protected:
        MaterialProperties at(const Point3D& p) const override
        {
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
