 #ifndef BITMAP_H
#define BITMAP_H

#include "color.h"
#include "util/position.h"
#include <memory>

class Bitmap final
{
private:
    std::unique_ptr<color[]> m_pixels;
    unsigned m_width;
    unsigned m_height;

public:
    Bitmap(unsigned width, unsigned height);
    Bitmap(const Bitmap&) = delete;
    Bitmap(Bitmap&&);

    bool is_inside(const position&) const;

    color& operator [](const position&);
    const color& operator [](const position&) const;

    unsigned width() const { return m_width; }
    unsigned height() const { return m_height; }

    void clear(const color&);
};

#endif
