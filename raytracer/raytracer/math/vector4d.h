#pragma once

#include "math/vector.h"
#include "math/approx.h"
#include "math/angle.h"
#include <iostream>


namespace math
{
    using Vector4D = Vector<4>;

    template<>
    struct approximately<Vector4D>
    {
        Vector4D value;
        double delta;

        explicit approximately(const Vector4D& value, double delta = 0.00001)
            :value(value), delta(delta)
        {
            // NOP
        }

        bool close_enough(const Vector4D& other) const
        {
            return (value - other).norm() < delta;
        }
    };
}
