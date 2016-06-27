#pragma once

#include "materials/brdf.h"


namespace raytracer
{
    namespace brdfs
    {
        namespace _private_
        {
            class Lambert : public BRDF
            {
            public:
                double evaluate(const math::Vector3D&, const math::Vector3D&) const override;
            };
        }
    }
}