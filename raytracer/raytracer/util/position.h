#ifndef POSITION_H
#define POSITION_H

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

    std::vector<position> around4() const
    {
        std::vector<position> result;

        result.push_back(this->moved(-1, 0));
        result.push_back(this->moved(1, 0));
        result.push_back(this->moved(0, -1));
        result.push_back(this->moved(0, 1));

        return result;
    }

    std::vector<position> around8() const
    {
        std::vector<position> result;

        for (int dy = -1; dy <= 1; ++dy)
        {
            for (int dx = -1; dx <= 1; ++dx)
            {
                if (dx != 0 || dy != 0)
                {
                    result.push_back(this->moved(dx, dy));
                }
            }
        }

        return result;
    }
};

#endif
