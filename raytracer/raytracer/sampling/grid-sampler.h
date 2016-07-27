#pragma once

#include "sampling/sampler.h"

namespace raytracer
{
    namespace samplers
    {
        namespace _private_
        {
            class GridSampler : public SamplerImplementation
            {
            public:
                GridSampler(unsigned rows, unsigned columns)
                    : m_rows(rows), m_columns(columns) { }

                void sample(const math::Rectangle2D& rectangle, std::function<void(const math::Point2D&)> function) const override;

            private:
                unsigned m_rows, m_columns;
            };
        }

        Sampler grid(unsigned rows, unsigned columns);
    }
}
