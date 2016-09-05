#pragma once

#include "imaging/bitmap.h"
#include "pipeline/consumer.h"


namespace demos
{
    // Example used in design documents
    void design_example(std::shared_ptr<raytracer::pipeline::Consumer<std::shared_ptr<imaging::Bitmap>>>);
}