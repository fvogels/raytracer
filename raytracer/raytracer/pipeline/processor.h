#pragma once

#include "pipeline/consumer.h"
#include "pipeline/producer.h"


namespace raytracer
{
    namespace pipeline
    {
        template<typename INPUT, typename OUTPUT>
        class Processor : public Consumer<INPUT>, public Producer<OUTPUT>
        {
            // EMPTY
        };
    }
}