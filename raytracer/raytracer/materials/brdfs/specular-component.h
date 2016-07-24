#pragma once

#include "materials/brdf.h"


namespace raytracer
{
    namespace brdfs
    {
        namespace _private_
        {
            class SpecularComponent : public BRDFBody
            {
            public:
                SpecularComponent(const imaging::Color&, double exponent);

                imaging::Color evaluate(const math::Vector3D&, const imaging::Color&, const math::Vector3D&, const math::Vector3D&) const override;

            private:
                imaging::Color m_color;
                double m_exponent;
            };
        }

        BRDF specular_component(const imaging::Color&, double exponent);
    }
}