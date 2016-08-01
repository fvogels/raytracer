#pragma once

#include "sampling/sampler.h"


namespace raytracer
{
    namespace samplers
    {
        Sampler stratified_jittered(unsigned, unsigned);
    }
}
