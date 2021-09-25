#include "tasks/parallel-task-scheduler.h"
#include "tasks/serial-task-scheduler.h"
#include <thread>
#include <atomic>
#include "easylogging++.h"

using namespace tasks;


namespace
{
    /// <summary>
    /// Performs tasks in parallel.
    /// </summary>
    class LoadBalancingParallelTaskScheduler : public tasks::schedulers::_private_::TaskSchedulerImplementation
    {
    public:
        LoadBalancingParallelTaskScheduler(unsigned thread_count)
            : m_thread_count(thread_count)
        {
            // NOP
        }

        void perform(std::vector<std::shared_ptr<Task>> tasks) const
        {
            std::atomic<unsigned> task_index(0);
            std::vector<std::thread> threads;

            for (unsigned k = 0; k != m_thread_count; ++k)
            {
                threads.push_back(std::thread([&]() {
                    unsigned current;

                    while ((current = task_index++) < tasks.size())
                    {
                        tasks[current]->perform();
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

TaskScheduler tasks::schedulers::load_balancing_parallel(unsigned thread_count)
{
    if (thread_count > 1)
    {
        LOG(INFO) << "Creating parallel scheduler with " << thread_count << " threads";

        return TaskScheduler(std::make_shared<LoadBalancingParallelTaskScheduler>(thread_count));
    }
    else
    {
        return tasks::schedulers::serial();
    }
}
