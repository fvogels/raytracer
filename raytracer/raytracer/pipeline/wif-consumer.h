#pragma once

#include "pipeline/processor.h"
#include "imaging/wif_format.h"
#include <string>


namespace raytracer
{
    namespace pipeline
    {
        std::shared_ptr<Consumer<std::shared_ptr<imaging::Bitmap>>> wif(const std::string&);
    }
}