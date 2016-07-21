#include "bitmap-consumers/wif-bitmap-consumer.h"

using namespace imaging;


std::shared_ptr<imaging::bitmap_consumers::_private_::WifBitmapConsumer> imaging::bitmap_consumers::wif(const std::string& path)
{
    return std::make_shared<imaging::bitmap_consumers::_private_::WifBitmapConsumer>(path);
}