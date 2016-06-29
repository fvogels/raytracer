#pragma once

#include "rendering/sampler.h"

namespace raytracer
{
    class SingleSampler : public Sampler
    {
    public:
        void sample(const math::Rectangle2D& rectangle, std::function<void(const math::Point2D&)> function) const override;
    };
}
