#pragma once

#include "tasks/task-scheduler.h"


namespace tasks
{
    namespace schedulers
    {
        /// <summary>
        /// Creates a scheduler that performs tasks in parallel, spread
        /// over <paramref name="thread_count" /> threads.
        /// </summary>
        TaskScheduler load_balancing_parallel(unsigned thread_count);
    }
}