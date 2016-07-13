#pragma once

#include "math/function.h"


namespace math
{
    namespace functions
    {
        template<typename R, typename T>
        math::Function<R, T> constant(R value)
        {
            std::function<R(T)> lambda = [value](T) {
                return value;
            };

            return from_lambda(lambda);
        }

        template<typename R>
        Function<R, R> identity()
        {
            return from_lambda<R, R>([](R x) { return x; });
        }
    }
}