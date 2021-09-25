#include "tasks/unbalanced-parallel-task-scheduler.h"
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
    class EqualLoadParallelTaskScheduler : public tasks::schedulers::_private_::TaskSchedulerImplementation
    {
    public:
        EqualLoadParallelTaskScheduler(unsigned thread_count)
            : m_thread_count(thread_count)
        {
            // NOP
        }

        void perform(std::vector<std::shared_ptr<Task>> tasks) const
        {
            std::vector<std::thread> threads;
            std::vector<std::vector<std::shared_ptr<Task>>> task_distribution(m_thread_count);

            for (unsigned k = 0; k != tasks.size(); ++k)
            {
                task_distribution[k % m_thread_count].push_back(tasks[k]);
            }

            for (unsigned k = 0; k != m_thread_count; ++k)
            {
                LOG(INFO) << "Thread " << k << " gets " << task_distribution[k].size() << " tasks";
            }

            for (unsigned k = 0; k != m_thread_count; ++k)
            {
                threads.push_back(std::thread([&task_distribution, k]() {
                    for (auto& task : task_distribution[k])
                    {
                        task->perform();
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

TaskScheduler tasks::schedulers::unbalanced_parallel(unsigned thread_count)
{
    if (thread_count > 1)
    {
        LOG(INFO) << "Creating equal load parallel scheduler with " << thread_count << " threads";

        return TaskScheduler(std::make_shared<EqualLoadParallelTaskScheduler>(thread_count));
    }
    else
    {
        return tasks::schedulers::serial();
    }
}
