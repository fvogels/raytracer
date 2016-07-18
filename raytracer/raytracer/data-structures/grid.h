#pragma once

#include "util/position.h"
#include <memory>
#include <functional>


namespace data
{
    template<typename T>
    class Grid
    {
    public:
        Grid(unsigned width, unsigned height, std::function<T(const position&)> initializer)
            : Grid(width, height)
        {
            for (unsigned y = 0; y != height; ++y)
            {
                for (unsigned x = 0; x != width; ++x)
                {
                    position p(x, y);

                    (*this)[p] = initializer(p);
                }
            }
        }

        Grid(unsigned width, unsigned height)
            : m_elts(std::make_unique<T[]>(width * height)), m_width(width), m_height(height)
        {
            // NOP
        }

        T& operator [](const position& p)
        {
            return m_elts[p.x + p.y * m_width];
        }

        const T& operator [](const position& p) const
        {
            return m_elts[p.x + p.y * m_width];
        }

        unsigned width() const
        {
            return m_width;
        }

        unsigned height() const
        {
            return m_height;
        }

    private:
        std::unique_ptr<T[]> m_elts;
        unsigned m_width;
        unsigned m_height;
    };
}