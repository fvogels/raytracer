#include "bitmap-consumers/motion-blur-consumer.h"
#include <assert.h>

using namespace imaging;


imaging::bitmap_consumers::_private_::MotionBlurBitmapConsumer::MotionBlurBitmapConsumer(const std::string& path)
    : m_wif(path), m_accumulation(nullptr), m_count(0)
{
    // NOP
}

imaging::bitmap_consumers::_private_::MotionBlurBitmapConsumer::~MotionBlurBitmapConsumer()
{
    for (unsigned y = 0; y != m_accumulation->height(); ++y)
    {
        for (unsigned x = 0; x != m_accumulation->width(); ++x)
        {
            Position p(x, y);

            (*m_accumulation)[p] /= m_count;
        }
    }

    m_wif.write_frame(*m_accumulation);
}

void imaging::bitmap_consumers::_private_::MotionBlurBitmapConsumer::consume(const Bitmap& bitmap)
{
    if (m_accumulation == nullptr)
    {
        m_accumulation = std::make_unique<Bitmap>(bitmap);
    }
    else
    {
        assert(m_accumulation->width() == bitmap.width());
        assert(m_accumulation->height() == bitmap.height());

        for (unsigned y = 0; y != bitmap.height(); ++y)
        {
            for (unsigned x = 0; x != bitmap.width(); ++x)
            {
                Position p(x, y);

                (*m_accumulation)[p] += bitmap[p];
            }
        }

        ++m_count;
    }
}

std::shared_ptr<imaging::bitmap_consumers::_private_::MotionBlurBitmapConsumer> imaging::bitmap_consumers::motion_blur(const std::string& path)
{
    return std::make_shared<imaging::bitmap_consumers::_private_::MotionBlurBitmapConsumer>(path);
}