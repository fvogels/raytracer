#pragma once

#include "imaging/color.h"
#include "util/position.h"
#include <memory>
#include <string>
#include <functional>


namespace imaging
{
    class Bitmap final
    {
    private:
        std::unique_ptr<color[]> m_pixels;
        unsigned m_width;
        unsigned m_height;

    public:
        Bitmap(unsigned width, unsigned height);
        Bitmap(const Bitmap&);
        Bitmap(Bitmap&&);

        bool is_inside(const position&) const;

        color& operator [](const position&);
        const color& operator [](const position&) const;

        unsigned width() const { return m_width; }
        unsigned height() const { return m_height; }

        void enumerate_positions(std::function<void(const position&)>) const;

        void clear(const color&);
    };

    Bitmap load_bitmap(const std::string& path);
    void save_bitmap(const std::string& path, const Bitmap& bitmap);
}
