#pragma once

#include "primitives/primitive.h"
#include <vector>
#include <memory>

namespace raytracer
{
    namespace primitives
    {
        namespace _private_
        {
            class Union : public PrimitiveImplementation
            {
            public:
                Union(std::vector<Primitive>&);

                bool find_hit(const math::Ray&, Hit*) const override;
                std::vector<std::shared_ptr<Hit>> hits(const math::Ray&) const override;
                math::Box bounding_box() const override;

            private:
                std::vector<Primitive> children;
            };
        }

        Primitive make_union(std::vector<Primitive>&);
    }
}