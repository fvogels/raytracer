#pragma once

#include "math/vector3d.h"
#include "math/point3d.h"
#include "math/matrix4d.h"
#include <iostream>

namespace math
{
    struct Ray final
    {
        Point3D origin;
        Vector3D direction;

        Ray(const Point3D& origin, const Vector3D& direction)
            : origin(origin), direction(direction) { }

        Ray(const Point3D& origin, const Point3D& through)
            : Ray(origin, through - origin) { }

        Ray(const Ray&) = default;

        Point3D at(double t) const { return origin + direction * t; }

        Ray transform(const Matrix4D&) const;
    };

    std::ostream& operator <<(std::ostream& out, const Ray&);
}