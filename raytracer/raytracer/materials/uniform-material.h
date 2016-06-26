#pragma once

#include "materials/material.h"

namespace raytracer
{
    namespace materials
    {
        class UniformMaterial : public MaterialImplementation
        {
        public:
            UniformMaterial(const imaging::color&, const imaging::color&, double);

            MaterialProperties at(const HitPosition&) const override;

        private:
            imaging::color m_diffuse;
            imaging::color m_specular;
            double m_specular_exponent;
        };
    }
}