#include "math/functions/random-function.h"
#include <array>

using namespace math;


math::Function<unsigned(unsigned)> math::functions::random_function(unsigned parameter)
{
    std::function<unsigned(unsigned)> lambda = [parameter](unsigned x) -> unsigned
    {
        std::array<unsigned, 16> xs = {
            0x49A40F45,
            0xF13FB1CC,
            0x76A12BC3,
            0x9075D13E,

            0x3F148AC9,
            0x13D67E10,
            0x7E79B3CA,
            0x4702F331,

            0x7213A977,
            0x347F8974,
            0x96FF641C,
            0xC78DD31A,

            0x13166A13,
            0x3789A110,
            0x18563DB3,
            0xB1675421
        };

        unsigned a = parameter;
        unsigned b = x;

        for (unsigned i = 0; i != 16; ++i)
        {
            a = (a << 1) ^ (a >> 1);
            b = b ^ xs[i];
            a += b;
            b *= a;
        }

        return a ^ b;
    };

    return from_lambda<unsigned, unsigned>(lambda);
}