#include "tasks/auto-parallelization-scheduler.h"
#include "easylogging++.h"

using namespace tasks;


namespace
{
    /// <summary>
    /// Performs tasks one after the other (i.e. not in parallel).
    /// </summary>
    class AutoParallelizationTaskScheduler : public tasks::schedulers::_private_::TaskSchedulerImplementation
    {
    public:
        void perform(std::vector<std::shared_ptr<Task>> tasks) const
        {
#           pragma loop(hint_parallel(8))
            for (size_t i = 0; i != tasks.size(); ++i)
                tasks[i]->perform();
        }
    };
}

TaskScheduler tasks::schedulers::auto_paralellization()
{
    LOG(INFO) << "Creating auto parallelization scheduler";

    return TaskScheduler(std::make_shared<AutoParallelizationTaskScheduler>());
}
