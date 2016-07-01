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
            class Transformer : public PrimitiveImplementation
            {
            public:
                Transformer(const math::Transformation& transformer, Primitive transformee)
                    : transformer(transformer), transformee(transformee) { }

                bool find_hit(const math::Ray&, Hit*) const override;
                std::vector<std::shared_ptr<Hit>> hits(const math::Ray&) const override;

            private:
                math::Transformation transformer;
                Primitive transformee;
            };
        }

        Primitive transform(const math::Transformation&, Primitive);
        Primitive translate(const math::Vector3D&, Primitive);
        Primitive scale(double, double, double, Primitive);
        Primitive rotate_around_x(math::Angle, Primitive);
        Primitive rotate_around_y(math::Angle, Primitive);
        Primitive rotate_around_z(math::Angle, Primitive);
    }
}