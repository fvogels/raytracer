#pragma once

#include <vector>

struct position final
{
    unsigned x, y;

    position(unsigned x, unsigned y)
        : x(x), y(y) { }

    void move(int dx, int dy)
    {
        x += dx;
        y += dy;
    }

    position moved(int dx, int dy) const
    {
        position copy = *this;
        copy.move(dx, dy);
        return copy;
    }
};
