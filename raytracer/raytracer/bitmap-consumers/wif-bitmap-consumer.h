#pragma once

#include "bitmap-consumers/bitmap-consumer.h"
#include "imaging/wif-format.h"
#include <string>


namespace imaging
{
    namespace bitmap_consumers
    {
        namespace _private_
        {
            class WifBitmapConsumer : public BitmapConsumer
            {
            public:
                WifBitmapConsumer(const std::string& path)
                    : m_wif(path)
                {
                    // NOP
                }

                void consume(const Bitmap& bitmap) override
                {
                    m_wif.write_frame(bitmap);
                }

            private:
                imaging::WIF m_wif;
            };
        }

        std::shared_ptr<_private_::WifBitmapConsumer> wif(const std::string&);
    }
}