#pragma once

#include <functional>
#include <memory>


namespace loopers
{
    class Looper
    {
    public:
        virtual void loop(unsigned, std::function<void(unsigned)>) const = 0;
    };
}