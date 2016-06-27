#pragma once

#include "materials/brdf.h"


namespace raytracer
{
    namespace brdfs
    {
        BRDF lambert(const imaging::color&);
    }
}