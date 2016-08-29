#include "materials/worley-material.h"
#include "math/functions/worley.h"
#include <cmath>

using namespace raytracer;
using namespace raytracer::materials;
using namespace math;
using namespace imaging;


namespace
{
    class WorleyMaterial3D : public raytracer::materials::_private_::MaterialImplementation
    {
    public:
        WorleyMaterial3D(double power)
            : m_noise_function(math::functions::worley3d()), m_power(power)
        {
            // NOP
        }

        MaterialProperties at(const HitPosition& hp) const override
        {
            Point3D p = hp.xyz;
            MaterialProperties properties(colors::black(), pow(this->m_noise_function(p), m_power) * colors::white(), colors::black(), 0.0, 0.0, 0.0, 0.0);

            return properties;
        }

    private:
        math::functions::Noise3D m_noise_function;
        double m_power;
    };
}

Material raytracer::materials::worley(double power)
{
    return Material(std::make_shared<WorleyMaterial3D>(power));
}