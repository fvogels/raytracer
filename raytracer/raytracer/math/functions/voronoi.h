#pragma once

#include "math/function.h"
#include "math/point.h"


namespace math
{
    namespace functions
    {
        math::Function<math::Point2D(const math::Point2D&)> voronoi2d(unsigned density, unsigned seed = 87);
        math::Function<math::Point3D(const math::Point3D&)> voronoi3d(unsigned density, unsigned seed = 87);
    }

    class Voronoi2D
    {
    public:
        virtual Point2D closest_to(const Point2D&) const = 0;
        virtual Point2D second_closest_to(const Point2D&) const = 0;
    };

    std::shared_ptr<Voronoi2D> voronoi2d(unsigned density, unsigned seed = 56373);
}