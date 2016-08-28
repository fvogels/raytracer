#pragma once

#include "imaging/color.h"
#include "math/ray.h"
#include "primitives/hit.h"
#include <limits>


namespace raytracer
{
    struct TraceResult
    {
        TraceResult(imaging::Color color, unsigned group_id, const math::Ray& ray, double t)
            : color(color), group_id(group_id), ray(ray), t(t) { }

        static TraceResult no_hit(const math::Ray& ray)
        {
            return TraceResult(imaging::colors::black(), MISSING_ID, ray, std::numeric_limits<double>::infinity());
        }

        imaging::Color color;
        unsigned group_id;
        math::Ray ray;
        double t;

        math::Point3D hit_position() const
        {
            return ray.at(t);
        }
    };
}