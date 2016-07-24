#pragma once

#include "imaging/bitmap.h"
#include <string>
#include <ostream>
#include <fstream>

namespace imaging
{
    class WIF
    {
    public:
        WIF(const std::string&);
        ~WIF();

        void write_frame(const Bitmap& bitmap);

    private:
        std::ofstream out;
    };
}