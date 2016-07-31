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
            class Bumpifier : public PrimitiveImplementation
            {
            public:
                Bumpifier(math::Function<math::Vector3D(const math::Point3D&)> normal_perturbator, Primitive perturbee)
                    : m_normal_perturbator(normal_perturbator), m_perturbee(perturbee) { }

                bool find_hit(const math::Ray&, Hit*) const override;
                std::vector<std::shared_ptr<Hit>> hits(const math::Ray&) const override;
                math::Box bounding_box() const override;

            private:
                void perturb(Hit*) const;

                math::Function<math::Vector3D(const math::Point3D&)> m_normal_perturbator;
                Primitive m_perturbee;
            };
        }

        Primitive bumpify(math::Function<math::Vector3D(const math::Point3D&)>, Primitive);
    }
}