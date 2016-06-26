#pragma once

namespace animation
{
    class Animation
    {
    public:
        virtual void update(double time) = 0;
    };
}