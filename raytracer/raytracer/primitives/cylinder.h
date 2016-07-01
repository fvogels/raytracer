#pragma once

#include "primitives/primitive.h"

namespace raytracer
{
    namespace primitives
    {
        namespace _private_
        {
            class CylinderX : public PrimitiveImplementation
            {
            public:
                bool find_hit(const math::Ray&, Hit*) const override;
                std::vector<std::shared_ptr<Hit>> hits(const math::Ray&) const override;                
                math::Box bounding_box() const override;
            };

            class CylinderY : public PrimitiveImplementation
            {
            public:
                bool find_hit(const math::Ray&, Hit*) const override;
                std::vector<std::shared_ptr<Hit>> hits(const math::Ray&) const override;
                math::Box bounding_box() const override;
            };

            class CylinderZ : public PrimitiveImplementation
            {
            public:
                bool find_hit(const math::Ray&, Hit*) const override;
                std::vector<std::shared_ptr<Hit>> hits(const math::Ray&) const override;
                math::Box bounding_box() const override;
            };
        }

        Primitive cylinder_along_x();
        Primitive cylinder_along_y();
        Primitive cylinder_along_z();
    }
}