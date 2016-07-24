#pragma once

#include "imaging/bitmap.h"


namespace imaging
{
    Bitmap load_bitmap(const std::string&);
    void save_bitmap(const std::string&, const Bitmap&);
}