#pragma once

#include "imaging/bitmap.h"
#include <ostream>


namespace imaging
{
    void write_text_ppm(const Bitmap&, std::ostream&);
    void write_binary_ppm(const Bitmap&, std::ostream&);
}