#include "bitmap.h"
#include <assert.h>


Bitmap::Bitmap(unsigned width, unsigned height)
    : m_width(width)
    , m_height(height)
    , m_pixels(std::move(std::make_unique<color[]>(width * height)))
{
    // NOP
}

Bitmap::Bitmap(Bitmap&& other)
    : m_width(other.m_width)
    , m_height(other.m_height)
    , m_pixels(std::move(other.m_pixels))
{
    // NOP
}

bool Bitmap::is_inside(const position& p) const
{
    return p.x < m_width && p.y < m_height;
}

color& Bitmap::operator[](const position& p)
{
    unsigned index = p.x + p.y * m_width;

    return m_pixels[index];
}

const color& Bitmap::operator[](const position& p) const
{
    assert(is_inside(p));

    unsigned index = p.x + p.y * m_width;
    return m_pixels[index];
}

void Bitmap::clear(const color& color)
{
    for (unsigned y = 0; y != m_height; ++y)
    {
        for (unsigned x = 0; x != m_width; ++x)
        {
            position p{ x, y };

            (*this)[p] = color;
        }
    }
}