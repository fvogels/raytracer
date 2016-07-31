#pragma once

#include "imaging/color.h"
#include "math/ray.h"
#include "primitives/hit.h"
#include <limits>


namespace raytracer
{
    struct TraceResult
    {
        static TraceResult no_hit()
        {
            return TraceResult(imaging::colors::black(), MISSING_ID, std::numeric_limits<double>::infinity());
        }

        TraceResult(imaging::Color color, unsigned group_id, double distance_to_hit)
            : color(color), group_id(group_id), distance_to_hit(distance_to_hit) { }

        imaging::Color color;
        unsigned group_id;
        double distance_to_hit;
    };
}