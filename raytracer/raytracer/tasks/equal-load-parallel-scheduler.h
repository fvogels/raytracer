#pragma once

#include "tasks/task-scheduler.h"


namespace tasks
{
    namespace schedulers
    {
        /// <summary>
        /// Creates a scheduler that performs tasks in parallels, spread
        /// over <paramref name="thread_count" /> threads.
        /// </summary>
        TaskScheduler equal_load_parallel(unsigned thread_count);
    }
}