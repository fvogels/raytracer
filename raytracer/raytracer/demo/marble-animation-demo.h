#pragma once

#include "bitmap-consumers/bitmap-consumer.h"
#include "pipeline/consumer.h"
#include <string>


namespace demos
{
    void marble(std::shared_ptr<raytracer::pipeline::Consumer<std::shared_ptr<imaging::Bitmap>>>);
}