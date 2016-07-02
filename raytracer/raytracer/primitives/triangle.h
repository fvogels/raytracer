#pragma once

#include "primitives/primitive.h"

namespace raytracer
{
    namespace primitives
    {
        namespace _private_
        {
            class Triangle : public PrimitiveImplementation
            {
            public:
                Triangle(const math::Point3D&, const math::Point3D&, const math::Point3D&);

                bool find_hit(const math::Ray&, Hit*) const override;
                std::vector<std::shared_ptr<Hit>> hits(const math::Ray&) const override;
                math::Box bounding_box() const override;

            private:
                math::Point3D m_a, m_b, m_c;
                math::Vector3D m_normal;
            };
        }

        Primitive triangle(const math::Point3D&, const math::Point3D&, const math::Point3D&);
    }
}