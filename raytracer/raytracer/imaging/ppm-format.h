#pragma once

#include "imaging/bitmap.h"
#include <ostream>


namespace imaging
{
    void write_ppm(const Bitmap&, std::ostream&);
}