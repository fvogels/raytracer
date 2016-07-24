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
    : m_pixels(width, height, colors::black())
{
    // NOP
}

unsigned imaging::Bitmap::width() const
{
    return m_pixels.width();
}

unsigned imaging::Bitmap::height() const
{
    return m_pixels.height();
}

bool imaging::Bitmap::is_inside(const position& p) const
{
    return p.x < width() && p.y < height();
}

color& imaging::Bitmap::operator[](const position& p)
{
    assert(is_inside(p));

    return m_pixels[p];
}

const color& imaging::Bitmap::operator[](const position& p) const
{
    assert(is_inside(p));

    return m_pixels[p];
}

void imaging::Bitmap::clear(const color& color)
{
    for_each_position([this, &color](const position& p) {
        m_pixels[p] = color;
    });
}

void imaging::Bitmap::for_each_position(std::function<void(const position&)> callback) const
{
    m_pixels.for_each_position(callback);
}

Bitmap& imaging::Bitmap::operator +=(const Bitmap& bitmap)
{
    assert(width() == bitmap.width());
    assert(height() == bitmap.height());

    for_each_position([this, &bitmap](const position& p) {
        (*this)[p] += bitmap[p];
    });

    return *this;
}

Bitmap& imaging::Bitmap::operator -=(const Bitmap& bitmap)
{
    assert(width() == bitmap.width());
    assert(height() == bitmap.height());

    for_each_position([this, &bitmap](const position& p) {
        (*this)[p] -= bitmap[p];
    });

    return *this;
}

Bitmap& imaging::Bitmap::operator *=(double constant)
{
    for_each_position([this, constant](const position& p) {
        (*this)[p] *= constant;
    });

    return *this;
}

Bitmap& imaging::Bitmap::operator /=(double constant)
{
    return *this *= 1 / constant;
}
