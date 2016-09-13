#pragma once

#include "math/rectangle2d.h"
#include "data-structures/position.h"

namespace math
{
    class Rasterizer
    {
    private:
        Rectangle2D rect;
        unsigned m_horizontal_subdivisions;
        unsigned m_vertical_subdivisions;

    public:
        Rasterizer(const Rectangle2D& rect, unsigned horizontal_subdivisions, unsigned vertical_subdivisions)
            : rect(rect), m_horizontal_subdivisions(horizontal_subdivisions), m_vertical_subdivisions(vertical_subdivisions) { }
        Rasterizer(const Rasterizer&) = default;

        Rasterizer& operator =(const Rasterizer&) = default;

        unsigned horizontal_subdivisions() const { return m_horizontal_subdivisions; }
        unsigned vertical_subdivisions() const { return m_vertical_subdivisions; }

        Rectangle2D operator [](const Position2D&) const;
    };
}
