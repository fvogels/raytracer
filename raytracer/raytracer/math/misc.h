#pragma once

namespace math
{
    template<typename T>
    constexpr T sign(T n)
    {
        return n < 0 ? -1 : (n > 0 ? 1 : 0);
    }    
}