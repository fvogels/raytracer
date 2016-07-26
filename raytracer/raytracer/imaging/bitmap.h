#pragma once

#include "imaging/color.h"
#include "data-structures/grid.h"
#include <memory>
#include <string>
#include <functional>


namespace imaging
{
    class Bitmap final
    {
    private:
        data::Grid<Color> m_pixels;

    public:
        Bitmap(unsigned, unsigned);
        Bitmap(const Bitmap&) = default;
        Bitmap(Bitmap&&) = default;

        bool is_inside(const Position&) const;

        Color& operator [](const Position&);
        const Color& operator [](const Position&) const;

        unsigned width() const;
        unsigned height() const;

        Bitmap& operator +=(const Bitmap&);
        Bitmap& operator -=(const Bitmap&);
        Bitmap& operator *=(double);
        Bitmap& operator /=(double);

        void for_each_position(std::function<void(const Position&)>) const;

        void clear(const Color&);
        void invert();
    };
}
