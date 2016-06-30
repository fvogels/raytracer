#pragma once

#include "primitives/primitive.h"
#include "math/function.h"
#include "math/interval.h"


namespace raytracer
{
    namespace primitives
    {
        namespace _private_
        {
            class Cropper : public PrimitiveImplementation
            {
            public:
                Cropper(Primitive, math::Function<bool, const math::Point3D&>);

                bool find_hit(const math::Ray&, Hit*) const override;
                std::vector<std::shared_ptr<Hit>> hits(const math::Ray&) const override;

            private:
                Primitive m_cropped;
                math::Function<bool, const math::Point3D&> m_predicate;
            };
        }

        Primitive crop(Primitive, math::Function<bool, const math::Point3D&>);
        Primitive crop_along_z(Primitive, const math::Interval<double>&);
    }
}