#include "imaging/ppm-format.h"
#include "math/interval.h"
#include <sstream>
#include <assert.h>

using namespace imaging;
using namespace math;


void imaging::write_ppm(const Bitmap& bitmap, std::ostream& out)
{
    const unsigned MAX_LEVEL = 255;

    std::stringstream headerStream;
    headerStream << "P6 " << bitmap.width() << " " << bitmap.height() << " " << MAX_LEVEL << " ";
    std::string header = headerStream.str();

    size_t headerSize = header.size();
    out.write(header.c_str(), headerSize);

    for (unsigned y = 0; y != bitmap.height(); ++y)
    {
        for (unsigned x = 0; x != bitmap.width(); ++x)
        {
            color c = bitmap[position(x, y)].clamped();

            assert(Interval<double>(0, 1).contains(c.r));
            assert(Interval<double>(0, 1).contains(c.g));
            assert(Interval<double>(0, 1).contains(c.b));

            uint8_t r = (uint8_t)(c.r * MAX_LEVEL);
            uint8_t g = (uint8_t)(c.g * MAX_LEVEL);
            uint8_t b = (uint8_t)(c.b * MAX_LEVEL);

            uint8_t rgb[3] = { r, g, b };

            out.write(reinterpret_cast<char*>(&rgb), sizeof(rgb));
        }
    }
}