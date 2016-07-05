#include "math/functions/random-function.h"

using namespace math;


math::Function<unsigned, unsigned> math::functions::random_function(unsigned parameter)
{
    std::function<unsigned(unsigned)> lambda = [parameter](unsigned x) -> unsigned
    {
        unsigned y = x ^ parameter ^ 0x3F78A401;
        unsigned z = x * 87984667 + y * 754136899 + 1324657;

        return x ^ z;
    };

    return from_lambda<unsigned, unsigned>(lambda);
}