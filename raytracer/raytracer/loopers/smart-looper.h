#pragma once

#include "loopers/looper.h"


namespace loopers
{
    std::shared_ptr<Looper> smart_looper(unsigned thread_count);
}