#pragma once

#include "imaging/color.h"
#include "util/position.h"
#include "data-structures/grid.h"
#include <memory>
#include <string>
#include <functional>


namespace imaging
{
    class Bitmap final
    {
    private:
        data::Grid<color> m_pixels;

    public:
        Bitmap(unsigned, unsigned);
        Bitmap(const Bitmap&) = default;
        Bitmap(Bitmap&&) = default;

        bool is_inside(const position&) const;

        color& operator [](const position&);
        const color& operator [](const position&) const;

        unsigned width() const;
        unsigned height() const;

        Bitmap& operator +=(const Bitmap&);
        Bitmap& operator -=(const Bitmap&);
        Bitmap& operator *=(double);
        Bitmap& operator /=(double);

        void for_each_position(std::function<void(const position&)>) const;

        void clear(const color&);
    };

    Bitmap load_bitmap(const std::string& path);
    void save_bitmap(const std::string& path, const Bitmap& bitmap);
}
