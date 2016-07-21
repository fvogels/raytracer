#include "bitmap-consumers/ppm-bitmap-consumer.h"
#include "imaging/ppm-format.h"


void imaging::bitmap_consumers::_private_::TextPpmBitmapConsumer::consume(const Bitmap& bitmap)
{
    write_text_ppm(bitmap, std::cout);
}

void imaging::bitmap_consumers::_private_::BinaryPpmBitmapConsumer::consume(const Bitmap& bitmap)
{
    write_binary_ppm(bitmap, std::cout);
}

std::shared_ptr<imaging::bitmap_consumers::_private_::TextPpmBitmapConsumer> imaging::bitmap_consumers::ppm_text()
{
    return std::make_shared<imaging::bitmap_consumers::_private_::TextPpmBitmapConsumer>();
}

std::shared_ptr<imaging::bitmap_consumers::_private_::BinaryPpmBitmapConsumer> imaging::bitmap_consumers::ppm_binary()
{
    return std::make_shared<imaging::bitmap_consumers::_private_::BinaryPpmBitmapConsumer>();
}