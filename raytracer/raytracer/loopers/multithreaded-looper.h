#pragma once

#include "loopers/looper.h"
#include <memory>


namespace loopers
{
    std::shared_ptr<Looper> multithreaded(unsigned);
}