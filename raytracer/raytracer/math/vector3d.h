#pragma once

#include "math/vector.h"
#include "math/approx.h"
#include "math/angle.h"
#include <iostream>


namespace math
{
    using Vector3D = Vector<3>;

    template<>
    struct approximately<Vector3D>
    {
        Vector3D value;
        double delta;

        explicit approximately(const Vector3D& value, double delta = 0.00001)
            :value(value), delta(delta)
        {
            // NOP
        }

        bool close_enough(const Vector3D& other) const
        {
            return (value - other).norm() < delta;
        }
    };
}