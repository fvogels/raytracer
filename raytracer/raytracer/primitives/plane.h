#pragma once

#include "primitives/primitive.h"

namespace raytracer
{
    namespace primitives
    {
        namespace _private_
        {
            class CoordinatePlane : public PrimitiveImplementation
            {
            public:
                std::vector<std::shared_ptr<Hit>> hits(const math::Ray&) const override;
            };

            class PlaneXY : public CoordinatePlane
            {
            public:
                bool find_hit(const math::Ray&, Hit*) const override;
            };

            class PlaneXZ : public CoordinatePlane
            {
            public:
                bool find_hit(const math::Ray&, Hit*) const override;
            };

            class PlaneYZ : public CoordinatePlane
            {
            public:
                bool find_hit(const math::Ray&, Hit*) const override;
            };
        }

        Primitive xy_plane();
        Primitive xz_plane();
        Primitive yz_plane();
    }
}