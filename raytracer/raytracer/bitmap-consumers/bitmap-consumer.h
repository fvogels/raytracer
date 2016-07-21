#pragma once

#include "imaging/bitmap.h"


namespace imaging
{
    class BitmapConsumer
    {
    public:
        virtual void consume(const Bitmap&) = 0;
        virtual void finish() = 0;
    };
}