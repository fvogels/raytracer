#pragma once

#include "imaging/bitmap.h"
#include "pipeline/consumer.h"
#include <string>


namespace demos
{
    void dalmatian(std::shared_ptr<raytracer::pipeline::Consumer<std::shared_ptr<imaging::Bitmap>>>);
}