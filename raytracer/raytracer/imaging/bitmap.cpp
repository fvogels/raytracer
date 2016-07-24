#include "imaging/bitmap.h"
#include <algorithm>
#include <assert.h>

using namespace imaging;


namespace
{
    std::unique_ptr<color[]> copy_pixels(color* cs, unsigned width, unsigned height)
    {
        auto result = std::make_unique<color[]>(width * height);

        for (size_t i = 0; i != width * height; ++i)
        {
            result[i] = cs[i];
        }

        return result;
    }
}


imaging::Bitmap::Bitmap(unsigned width, unsigned height)
    : m_width(width)
    , m_height(height)
    , m_pixels(std::move(std::make_unique<color[]>(width * height)))
{
    // NOP
}

imaging::Bitmap::Bitmap(const Bitmap& bitmap)
    : m_width(bitmap.m_width)
    , m_height(bitmap.m_height)
    , m_pixels(std::move(copy_pixels(bitmap.m_pixels.get(), bitmap.m_width, bitmap.m_height)))
{
    // NOP
}

imaging::Bitmap::Bitmap(Bitmap&& other)
    : m_width(other.m_width)
    , m_height(other.m_height)
    , m_pixels(std::move(other.m_pixels))
{
    // NOP
}

bool imaging::Bitmap::is_inside(const position& p) const
{
    return p.x < m_width && p.y < m_height;
}

color& imaging::Bitmap::operator[](const position& p)
{
    unsigned index = p.x + p.y * m_width;

    return m_pixels[index];
}

const color& imaging::Bitmap::operator[](const position& p) const
{
    assert(is_inside(p));

    unsigned index = p.x + p.y * m_width;
    return m_pixels[index];
}

void imaging::Bitmap::clear(const color& color)
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

void imaging::Bitmap::enumerate_positions(std::function<void(const position&)> callback) const
{
    for (unsigned y = 0; y != m_height; ++y)
    {
        for (unsigned x = 0; x != m_width; ++x)
        {
            callback(position(x, y));
        }
    }
}

Bitmap& imaging::Bitmap::operator +=(const Bitmap& bitmap)
{
    assert(m_width == bitmap.m_width);
    assert(m_height == bitmap.m_height);

    enumerate_positions([this, &bitmap](const position& p) {
        (*this)[p] += bitmap[p];
    });

    return *this;
}

Bitmap& imaging::Bitmap::operator -=(const Bitmap& bitmap)
{
    assert(m_width == bitmap.m_width);
    assert(m_height == bitmap.m_height);

    enumerate_positions([this, &bitmap](const position& p) {
        (*this)[p] -= bitmap[p];
    });

    return *this;
}

Bitmap& imaging::Bitmap::operator *=(double constant)
{
    enumerate_positions([this, constant](const position& p) {
        (*this)[p] *= constant;
    });

    return *this;
}

Bitmap& imaging::Bitmap::operator /=(double constant)
{
    return *this *= 1 / constant;
}
