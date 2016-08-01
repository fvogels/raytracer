#pragma once

#include "imaging/bitmap.h"
#include "pipeline/consumer.h"


namespace demos
{
    void split_depth(std::shared_ptr<raytracer::pipeline::Consumer<std::shared_ptr<imaging::Bitmap>>>);
}