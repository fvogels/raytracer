#pragma once

#include <cstdint>
#include "imaging/color.h"


namespace imaging
{
    namespace wif
    {
        namespace _private_
        {
            struct RGB
            {
                uint8_t r;
                uint8_t g;
                uint8_t b;
            };

            void convert(const RGB& rgb, imaging::Color* color)
            {
                color->r = rgb.r / 255.0;
                color->g = rgb.g / 255.0;
                color->b = rgb.b / 255.0;
            }
        }
    }
}