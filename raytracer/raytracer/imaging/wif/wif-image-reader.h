#pragma once

#include "imaging/image-reader.h"
#include <memory>
#include <string>


namespace imaging
{
    namespace wif
    {
        std::unique_ptr<imaging::ImageReader> create_image_reader();

        imaging::Bitmap load(const std::string& path);
    }
}