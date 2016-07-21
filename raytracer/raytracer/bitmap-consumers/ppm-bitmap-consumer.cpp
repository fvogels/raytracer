#include "bitmap-consumers/ppm-bitmap-consumer.h"
#include "imaging/ppm-format.h"


void imaging::bitmap_consumers::_private_::PpmBitmapConsumer::consume(const Bitmap& bitmap)
{
    write_ppm(bitmap, std::cout);
}

std::shared_ptr<imaging::bitmap_consumers::_private_::PpmBitmapConsumer> imaging::bitmap_consumers::ppm()
{
    return std::make_shared<imaging::bitmap_consumers::_private_::PpmBitmapConsumer>();
}