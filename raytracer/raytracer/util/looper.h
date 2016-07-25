#pragma once

#include <functional>
#include <memory>


namespace util
{
    class Looper
    {
    public:
        virtual void loop(unsigned, std::function<void(unsigned)>) const = 0;
    };

    namespace loopers
    {
        std::shared_ptr<Looper> single_threaded();
        std::shared_ptr<Looper> multithreaded(unsigned);
        std::shared_ptr<Looper> looper(unsigned);
    }
}