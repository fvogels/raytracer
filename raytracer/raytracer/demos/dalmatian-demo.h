#pragma once

#include "imaging/bitmap.h"
#include "pipeline/consumer.h"
#include <string>


namespace demos
{
    void dalmatian2d(std::shared_ptr<raytracer::pipeline::Consumer<std::shared_ptr<imaging::Bitmap>>>);
    void dalmatian3d(std::shared_ptr<raytracer::pipeline::Consumer<std::shared_ptr<imaging::Bitmap>>>);
}