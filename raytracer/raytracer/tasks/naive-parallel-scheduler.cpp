#include "tasks/naive-parallel-scheduler.h"
#include "easylogging++.h"
#include <thread>

using namespace tasks;


namespace
{
    /// <summary>
    /// Performs tasks one after the other (i.e. not in parallel).
    /// </summary>
    class NaiveTaskScheduler : public tasks::schedulers::_private_::TaskSchedulerImplementation
    {
    public:
        void perform(std::vector<std::shared_ptr<Task>> tasks) const
        {
            std::vector<std::thread> threads;

            for (auto task : tasks)
            {
                threads.push_back(std::thread([task]() {
                    task->perform();
                }));
            }

            for (auto& thread : threads)
            {
                thread.join();
            }
        }
    };
}

TaskScheduler tasks::schedulers::naive_parallel()
{
    LOG(INFO) << "Creating naive parallel scheduler";

    return TaskScheduler(std::make_shared<NaiveTaskScheduler>());
}
