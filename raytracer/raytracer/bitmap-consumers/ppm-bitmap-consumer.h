#pragma once

#include "bitmap-consumers/bitmap-consumer.h"
#include <string>


namespace imaging
{
    namespace bitmap_consumers
    {
        namespace _private_
        {
            class TextPpmBitmapConsumer : public BitmapConsumer
            {
            public:
                void consume(const Bitmap& bitmap) override;
            };

            class BinaryPpmBitmapConsumer : public BitmapConsumer
            {
            public:
                void consume(const Bitmap& bitmap) override;
            };
        }

        std::shared_ptr<_private_::TextPpmBitmapConsumer> ppm_text();
        std::shared_ptr<_private_::BinaryPpmBitmapConsumer> ppm_binary();
    }
}