#pragma once

#include "materials/material.h"
#include "math/functions/noise.h"


namespace raytracer
{
    namespace materials
    {
        namespace _private_
        {
            class WorleyMaterial3D : public _private_::MaterialImplementation
            {
            public:
                WorleyMaterial3D();

                MaterialProperties at(const HitPosition&) const override;

            private:
                math::functions::Noise3D m_noise_function;
            };
        }

        Material worley();
    }
}