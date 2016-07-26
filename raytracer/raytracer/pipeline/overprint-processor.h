#pragma once

#include "pipeline/processor.h"
#include "imaging/bitmap.h"


namespace raytracer
{
    namespace pipeline
    {
        std::shared_ptr<Processor<std::shared_ptr<imaging::Bitmap>, std::shared_ptr<imaging::Bitmap>>> overprint();
    }
}