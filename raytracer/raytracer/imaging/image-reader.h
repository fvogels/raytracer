#pragma once

#include "imaging/bitmap.h"
#include "io/binary-reader.h"


namespace imaging
{
    class ImageReader
    {
    public:
        virtual imaging::Bitmap read(io::BinaryReader& reader) const = 0;
    };
}
