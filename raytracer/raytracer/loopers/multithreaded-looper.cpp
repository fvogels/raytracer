#include "loopers/multithreaded-looper.h"
#include <thread>
#include <atomic>
#include <vector>

using namespace loopers;


namespace
{
    class MultithreadedLooper : public Looper
    {
    public:
        MultithreadedLooper(unsigned thread_count)
            : m_thread_count(thread_count)
        {
            // NOP
        }

        void loop(unsigned max, std::function<void(unsigned)> body) const
        {
            std::atomic<unsigned> i(0);
            std::vector<std::thread> threads;

            for (unsigned k = 0; k != m_thread_count; ++k)
            {
                threads.push_back(std::thread([&]() {
                    unsigned current;

                    while ((current = i++) < max)
                    {
                        body(current);
                    }
                }));
            }

            for (auto& thread : threads)
            {
                thread.join();
            }
        }

    private:
        unsigned m_thread_count;
    };
}

std::shared_ptr<Looper> loopers::multithreaded(unsigned thread_count)
{
    return std::make_shared<MultithreadedLooper>(thread_count);
}
