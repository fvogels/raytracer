#pragma once

#include "materials/brdf.h"


namespace raytracer
{
    namespace brdfs
    {
        BRDF phong(const imaging::color&, const imaging::color&, double);
    }
}