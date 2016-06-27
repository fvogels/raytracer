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
                SpecularComponent(const imaging::color&);

                imaging::color evaluate(const math::Vector3D&, const imaging::color&, const math::Vector3D&, const math::Vector3D&) const override;

            private:
                imaging::color m_color;
            };
        }

        BRDF specular_component(const imaging::color&);
    }
}