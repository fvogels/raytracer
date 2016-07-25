#include "wif-format.h"
#include "easylogging++.h"

using namespace imaging;

namespace
{
    struct RGBColor
    {
        uint8_t r, g, b;

        RGBColor(const Color& c)
        {
            Color clamped = c.clamped();

            r = uint8_t(clamped.r * 255);
            g = uint8_t(clamped.g * 255);
            b = uint8_t(clamped.b * 255);
        }
    };
}


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
    TIMED_FUNC(timerObj);

    uint32_t width = bitmap.width();
    uint32_t height = bitmap.height();   

    out.write(reinterpret_cast<char*>(&width), sizeof(uint32_t));
    out.write(reinterpret_cast<char*>(&height), sizeof(uint32_t));

    for (unsigned j = 0; j != bitmap.height(); ++j)
    {
        for (unsigned i = 0; i != bitmap.width(); ++i)
        {
            RGBColor RGBColor(bitmap[Position(i, j)]);

            out.write(reinterpret_cast<char*>(&RGBColor), sizeof(RGBColor));
        }
    }
}