#include "loopers/smart-looper.h"
#include "loopers/single-threaded-looper.h"
#include "loopers/multithreaded-looper.h"

using namespace loopers;


std::shared_ptr<Looper> loopers::smart_looper(unsigned thread_count)
{
    if (thread_count == 1)
    {
        return single_threaded();
    }
    else
    {
        return multithreaded(thread_count);
    }
}
