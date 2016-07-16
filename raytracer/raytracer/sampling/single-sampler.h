#pragma once

#include "sampling/sampler.h"

namespace raytracer
{
    namespace samplers
    {
        namespace _private_
        {
            class SingleSampler : public SamplerImplementation
            {
            public:
                void sample(const math::Rectangle2D& rectangle, std::function<void(const math::Point2D&)> function) const override;
            };
        }

        Sampler single();
    }
}
