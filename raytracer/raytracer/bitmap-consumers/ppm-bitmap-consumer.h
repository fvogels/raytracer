#pragma once

#include "bitmap-consumers/bitmap-consumer.h"
#include <string>


namespace imaging
{
    namespace bitmap_consumers
    {
        namespace _private_
        {
            class PpmBitmapConsumer : public BitmapConsumer
            {
            public:
                void consume(const Bitmap& bitmap) override;
            };
        }

        std::shared_ptr<_private_::PpmBitmapConsumer> ppm();
    }
}