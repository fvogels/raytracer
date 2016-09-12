#pragma once

#include "imaging/bitmap.h"
#include "pipeline/consumer.h"


namespace demos
{
    void bumpify_plane(std::shared_ptr<raytracer::pipeline::Consumer<std::shared_ptr<imaging::Bitmap>>>);
}