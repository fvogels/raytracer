#pragma once

#include <iostream>


struct Position final
{
    unsigned x, y;

    Position(unsigned x, unsigned y)
        : x(x), y(y) { }

    void move(int dx, int dy)
    {
        x += dx;
        y += dy;
    }

    Position moved(int dx, int dy) const
    {
        Position copy = *this;
        copy.move(dx, dy);
        return copy;
    }
};

inline std::ostream& operator <<(std::ostream& out, const Position& p)
{
    return out << "(" << p.x << "," << p.y << ")";
}