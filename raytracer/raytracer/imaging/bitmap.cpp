#include "imaging/bitmap.h"
#include <algorithm>
#include <assert.h>

using namespace imaging;


namespace
{
    std::unique_ptr<Color[]> copy_pixels(Color* cs, unsigned width, unsigned height)
    {
        auto result = std::make_unique<Color[]>(width * height);

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

bool imaging::Bitmap::is_inside(const Position& p) const
{
    return p.x < width() && p.y < height();
}

Color& imaging::Bitmap::operator[](const Position& p)
{
    assert(is_inside(p));

    return m_pixels[p];
}

const Color& imaging::Bitmap::operator[](const Position& p) const
{
    assert(is_inside(p));

    return m_pixels[p];
}

void imaging::Bitmap::clear(const Color& Color)
{
    for_each_position([this, &Color](const Position& p) {
        m_pixels[p] = Color;
    });
}

void imaging::Bitmap::for_each_position(std::function<void(const Position&)> callback) const
{
    m_pixels.for_each_position(callback);
}

Bitmap& imaging::Bitmap::operator +=(const Bitmap& bitmap)
{
    assert(width() == bitmap.width());
    assert(height() == bitmap.height());

    for_each_position([this, &bitmap](const Position& p) {
        (*this)[p] += bitmap[p];
    });

    return *this;
}

Bitmap& imaging::Bitmap::operator -=(const Bitmap& bitmap)
{
    assert(width() == bitmap.width());
    assert(height() == bitmap.height());

    for_each_position([this, &bitmap](const Position& p) {
        (*this)[p] -= bitmap[p];
    });

    return *this;
}

Bitmap& imaging::Bitmap::operator *=(double constant)
{
    for_each_position([this, constant](const Position& p) {
        (*this)[p] *= constant;
    });

    return *this;
}

Bitmap& imaging::Bitmap::operator /=(double constant)
{
    return *this *= 1 / constant;
}
