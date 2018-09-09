#pragma once

#include "pipeline/processor.h"
#include "imaging/bitmap.h"
#include <string>
#include <memory>


namespace raytracer
{
    namespace pipeline
    {
        std::shared_ptr<Consumer<std::shared_ptr<imaging::Bitmap>>> ppm();
    }
}