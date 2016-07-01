#pragma once

#include "primitives/primitive.h"
#include "materials/material.h"
#include <memory>

namespace raytracer
{
    namespace primitives
    {
        namespace _private_
        {
            class Decorator : public PrimitiveImplementation
            {
            public:
                Decorator(Material, Primitive);

                virtual bool find_hit(const math::Ray&, Hit*) const override;
                std::vector<std::shared_ptr<Hit>> hits(const math::Ray&) const override;
                math::Box bounding_box() const override;

            private:
                Material material;
                Primitive child;
            };
        }

        Primitive decorate(Material, Primitive);
    }
}