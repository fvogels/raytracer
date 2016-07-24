#include "wif_format.h"

using namespace imaging;


struct RGB
{
    uint8_t r, g, b;

    RGB(const Color& c)
    {
        Color clamped = c.clamped();

        r = uint8_t(clamped.r * 255);
        g = uint8_t(clamped.g * 255);
        b = uint8_t(clamped.b * 255);
    }
};


imaging::WIF::WIF(const std::string& path) : out(path, std::ios::binary)
{
    // NOP
}

imaging::WIF::~WIF()
{
    uint32_t datum = 0;

    out.write(reinterpret_cast<char*>(&datum), sizeof(uint32_t));
}

void imaging::WIF::write_frame(const Bitmap& bitmap)
{
    uint32_t width = bitmap.width();
    uint32_t height = bitmap.height();

    out.write(reinterpret_cast<char*>(&width), sizeof(uint32_t));
    out.write(reinterpret_cast<char*>(&height), sizeof(uint32_t));

    for (unsigned j = 0; j != bitmap.height(); ++j)
    {
        for (unsigned i = 0; i != bitmap.width(); ++i)
        {
            RGB rgb(bitmap[Position(i, j)]);

            out.write(reinterpret_cast<char*>(&rgb), sizeof(RGB));
        }
    }
}