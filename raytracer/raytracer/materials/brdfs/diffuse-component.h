#pragma once

#include "materials/brdf.h"


namespace raytracer
{
    namespace brdfs
    {
        namespace _private_
        {
            class DiffuseComponent : public BRDFBody
            {
            public:
                DiffuseComponent(const imaging::Color&);

                imaging::Color evaluate(const math::Vector3D&, const imaging::Color&, const math::Vector3D&, const math::Vector3D&) const override;

            private:
                imaging::Color m_color;
            };
        }

        BRDF diffuse_component(const imaging::Color&);
    }
}