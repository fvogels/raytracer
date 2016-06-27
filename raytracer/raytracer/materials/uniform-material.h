#pragma once

#include "materials/material.h"

namespace raytracer
{
    namespace materials
    {
        class UniformMaterial : public MaterialImplementation
        {
        public:
            UniformMaterial(const MaterialProperties&);

            MaterialProperties at(const HitPosition&) const override;

        private:
            MaterialProperties m_properties;
        };
    }
}