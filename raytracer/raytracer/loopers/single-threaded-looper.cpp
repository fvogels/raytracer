#include "loopers/single-threaded-looper.h"

using namespace loopers;


namespace
{
    class SingleThreadedLooper : public Looper
    {
    public:
        void loop(unsigned max, std::function<void(unsigned)> body) const
        {
            for (unsigned i = 0; i != max; ++i)
            {
                body(i);
            }
        }
    };
}

std::shared_ptr<Looper> loopers::single_threaded()
{
    return std::make_shared<SingleThreadedLooper>();
}
