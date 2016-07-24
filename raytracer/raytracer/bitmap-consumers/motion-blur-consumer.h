#pragma once

#include "bitmap-consumers/bitmap-consumer.h"
#include "imaging/wif-format.h"
#include <memory>
#include <string>


namespace imaging
{
    namespace bitmap_consumers
    {
        namespace _private_
        {
            class MotionBlurBitmapConsumer : public BitmapConsumer
            {
            public:
                MotionBlurBitmapConsumer(const std::string&);
                ~MotionBlurBitmapConsumer();

                void consume(const Bitmap& bitmap) override;

            private:
                std::unique_ptr<Bitmap> m_accumulation;
                unsigned m_count;
                WIF m_wif;
            };
        }

        std::shared_ptr<_private_::MotionBlurBitmapConsumer> motion_blur(const std::string&);
    }
}