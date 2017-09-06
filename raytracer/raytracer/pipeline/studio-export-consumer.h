#pragma once

#include "pipeline/consumer.h"
#include "imaging/bitmap.h"
#include <string>


namespace raytracer
{
    namespace pipeline
    {
        std::shared_ptr<Consumer<std::shared_ptr<imaging::Bitmap>>> studio_exporter();
    }
}