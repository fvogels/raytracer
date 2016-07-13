#pragma once

#include "materials/material.h"
#include "math/functions/noise.h"


namespace raytracer
{
    namespace materials
    {
        namespace _private_
        {
            class PerlinMaterial2D : public _private_::MaterialImplementation
            {
            public:
                PerlinMaterial2D();

                MaterialProperties at(const HitPosition&) const override;

            private:
                math::functions::Noise2D m_noise_function;
            };
        }

        Material perlin2d();
    }
}