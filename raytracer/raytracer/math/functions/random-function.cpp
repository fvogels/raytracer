#include "math/functions/random-function.h"

using namespace math;


math::Function<unsigned, unsigned> math::functions::random_function(unsigned parameter)
{
    std::function<unsigned(unsigned)> lambda = [parameter](unsigned x) -> unsigned
    {
        unsigned a = x ^ 0x71F38A01;
        unsigned b = x ^ 0x3049F1BC;
        unsigned c = parameter * a * b * x;

        return a ^ b ^ c ^ parameter;
    };

    return from_lambda<unsigned, unsigned>(lambda);
}