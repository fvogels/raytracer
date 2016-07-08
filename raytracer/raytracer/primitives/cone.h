#pragma once

#include "primitives/primitive.h"

namespace raytracer
{
    namespace primitives
    {
        namespace _private_
        {
            class ConeZ : public PrimitiveImplementation
            {
            public:
                bool find_hit(const math::Ray&, Hit*) const override;
                std::vector<std::shared_ptr<Hit>> hits(const math::Ray&) const override;
                math::Box bounding_box() const override;
            };
        }

        Primitive cone_along_z();
    }
}