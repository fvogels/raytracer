#pragma once

#include "math/function.h"


namespace math
{
    namespace functions
    {
        template<typename R>
        Function<R, R> identity()
        {
            return from_lambda<R, R>([](R x) { return x; });
        }
    }
}
