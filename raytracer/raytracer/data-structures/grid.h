#pragma once

#include "data-structures/position.h"
#include <memory>
#include <functional>


namespace data
{
    template<typename T>
    class Grid
    {
    public:
        Grid(unsigned width, unsigned height, std::function<T(const Position&)> initializer)
            : Grid(width, height)
        {
            for (unsigned y = 0; y != height; ++y)
            {
                for (unsigned x = 0; x != width; ++x)
                {
                    Position p(x, y);

                    (*this)[p] = initializer(p);
                }
            }
        }

        Grid(unsigned width, unsigned height, T initial_value)
            : Grid(width, height, [&initial_value](const Position&) { return initial_value; })
        {
            // NOP
        }

        Grid(unsigned width, unsigned height)
            : m_elts(std::make_unique<T[]>(width * height)), m_width(width), m_height(height)
        {
            // NOP
        }

        Grid(const Grid<T>& grid)
            : Grid(grid.width(), grid.height(), [&grid](const Position& p) { return grid[p]; })
        {
            // NOP
        }

        T& operator [](const Position& p)
        {
            return m_elts[p.x + p.y * m_width];
        }

        const T& operator [](const Position& p) const
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

        bool is_inside(const Position& p) const
        {
            return p.x < m_width && p.y < m_height;
        }

        void around(const Position& p, unsigned distance, std::function<void(const Position&)> callback) const
        {
            int dist = int(distance);

            for (int dx = -dist; dx <= dist; ++dx)
            {
                for (int dy = -dist; dy <= dist; ++dy)
                {
                    Position q(p.x + dx, p.y + dy);

                    if (is_inside(q))
                    {
                        callback(q);
                    }
                }
            }
        }

        void for_each_position(std::function<void(const Position&)> callback) const
        {
            for (unsigned y = 0; y != m_height; ++y)
            {
                for (unsigned x = 0; x != m_width; ++x)
                {
                    callback(Position(x, y));
                }
            }
        }

    private:
        std::unique_ptr<T[]> m_elts;
        unsigned m_width;
        unsigned m_height;
    };
}