#pragma once

#include "materials/brdf.h"


namespace raytracer
{
    namespace brdfs
    {
        namespace _private_
        {
            class Lambert : public BRDFBody
            {
            public:
                Lambert(const imaging::color&);

                imaging::color evaluate(const math::Vector3D&, const imaging::color&, const math::Vector3D&, const math::Vector3D&) const override;

            private:
                imaging::color m_color;
            };
        }

        BRDF lambert(const imaging::color&);
    }
}