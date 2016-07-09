#pragma once

#include "rendering/sampler.h"

namespace raytracer
{
    namespace samplers
    {
        namespace _private_
        {
            class GridSampler : public SamplerImplementation
            {
            public:
                GridSampler(int rows, int columns)
                    : rows(rows), columns(columns) { }

                void sample(const math::Rectangle2D& rectangle, std::function<void(const math::Point2D&)> function) const override;

            private:
                int rows, columns;
            };
        }

        Sampler grid(int rows, int columns);
    }
}
