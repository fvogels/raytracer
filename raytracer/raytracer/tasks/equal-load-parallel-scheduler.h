#pragma once

#include "tasks/task-scheduler.h"


namespace tasks
{
    namespace schedulers
    {
        TaskScheduler equal_load_parallel(unsigned thread_count);
    }
}