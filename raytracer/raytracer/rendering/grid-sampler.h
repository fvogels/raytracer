#pragma once

#include "renderer/sampler.h"

namespace raytracer
{
    class GridSampler : public Sampler
    {
    public:
        GridSampler(int rows, int columns)
            : rows(rows), columns(columns) { }

        void sample(const math::Rectangle2D& rectangle, std::function<void(const math::Point2D&)> function) const override;

    private:
        int rows, columns;
    };
}