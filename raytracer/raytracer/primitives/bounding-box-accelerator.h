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
            class BoundingBoxAccelerator : public PrimitiveImplementation
            {
            public:
                BoundingBoxAccelerator(Primitive);

                bool find_hit(const math::Ray&, Hit*) const override;
                std::vector<std::shared_ptr<Hit>> hits(const math::Ray&) const override;
                math::Box bounding_box() const override;

            private:
                Primitive m_child;
                math::Box m_bounding_box;
            };
        }

        Primitive bounding_box_accelerator(Primitive);
    }
}