#pragma once

#include "primitives/primitive.h"
#include "math/transformation.h"
#include <memory>

namespace raytracer
{
    namespace primitives
    {
        namespace _private_
        {
            class Group : public PrimitiveImplementation
            {
            public:
                Group(unsigned, Primitive);

                bool find_hit(const math::Ray&, Hit*) const override;
                std::vector<std::shared_ptr<Hit>> hits(const math::Ray&) const override;
                math::Box bounding_box() const override;

            private:
                Primitive m_child;
                unsigned m_id;
            };
        }

        Primitive group(unsigned, Primitive);
    }
}