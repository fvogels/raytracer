#ifdef TEST_BUILD

#include "Catch.h"
#include "math/functions/easing-functions.h"

using namespace math;
using namespace math::functions;
using namespace math::functions::easing;

namespace
{
    double lderivative(Function<double(double)> f, double x, double dx = 0.00000001)
    {
        return (f(x + dx) - f(x)) / dx;
    }

    double rderivative(Function<double(double)> f, double x, double dx = 0.00000001)
    {
        return (f(x) - f(x - dx)) / dx;
    }
}


TEST_CASE("[EasingFunctions] Linear)", "[EasingFunctions]")
{
    auto f = easing_function<LINEAR>();

    CHECK(f(0) == Approx(0));
    CHECK(f(1) == Approx(1));
    CHECK(lderivative(f, 0) == Approx(1));
    CHECK(rderivative(f, 1) == Approx(1));
}

TEST_CASE("[EasingFunctions] Linear with dy=5)", "[EasingFunctions]")
{
    auto f = easing_function<LINEAR>(dy(5));

    CHECK(f(0) == Approx(0));
    CHECK(f(1) == Approx(5));
    CHECK(lderivative(f, 0) == Approx(5));
    CHECK(rderivative(f, 1) == Approx(5));
}

TEST_CASE("[EasingFunctions] Linear with y=1..7)", "[EasingFunctions]")
{
    auto f = easing_function<LINEAR>(y_range(1, 7));

    CHECK(f(0) == Approx(1));
    CHECK(f(1) == Approx(7));
    CHECK(lderivative(f, 0) == Approx(6));
    CHECK(rderivative(f, 1) == Approx(6));
}

TEST_CASE("[EasingFunctions] Linear with dx=3, y=1..7)", "[EasingFunctions]")
{
    auto f = easing_function<LINEAR>(dx(3), y_range(1, 7));

    CHECK(f(0) == Approx(1));
    CHECK(f(3) == Approx(7));
    CHECK(lderivative(f, 1) == Approx(2));
    CHECK(rderivative(f, 3) == Approx(2));
}

TEST_CASE("[EasingFunctions] Linear with x=1..3, y=1..7)", "[EasingFunctions]")
{
    auto f = easing_function<LINEAR>(x_range(1, 3), y_range(1, 7));

    CHECK(f(1) == Approx(1));
    CHECK(f(3) == Approx(7));
    CHECK(lderivative(f, 1) == Approx(3));
    CHECK(rderivative(f, 3) == Approx(3));
}

TEST_CASE("[EasingFunctions] QuadraticIn with x=2..3, y=3..7)", "[EasingFunctions]")
{
    auto f = easing_function<QUADRATIC, in>(x_range(2, 3), y_range(3, 7));

    CHECK(f(2) == Approx(3));
    CHECK(f(3) == Approx(7));
    CHECK(lderivative(f, 2) == Approx(0));
}

TEST_CASE("[EasingFunctions] QuadraticOut with x=2..3, y=3..7)", "[EasingFunctions]")
{
    auto f = easing_function<QUADRATIC, out>(x_range(2, 3), y_range(3, 7));

    CHECK(f(2) == Approx(3));
    CHECK(f(3) == Approx(7));
    CHECK(rderivative(f, 3) == Approx(0));
}

TEST_CASE("[EasingFunctions] QuadraticInOut with x=0..1, y=0..1)", "[EasingFunctions]")
{
    auto f = easing_function<QUADRATIC, inout>();

    CHECK(f(0) == Approx(0));
    CHECK(f(1) == Approx(1));
    CHECK(lderivative(f, 0) == Approx(0).epsilon(0.000001));
    CHECK(rderivative(f, 1) == Approx(0).epsilon(0.000001));
}

TEST_CASE("[EasingFunctions] QuadraticInOut with x=2..3, y=3..7)", "[EasingFunctions]")
{
    auto f = easing_function<QUADRATIC, inout>(x_range(2, 3), y_range(3, 7));

    CHECK(f(2) == Approx(3));
    CHECK(f(3) == Approx(7));
    CHECK(lderivative(f, 2) == Approx(0).epsilon(0.000001));
    CHECK(rderivative(f, 3) == Approx(0).epsilon(0.000001));
}

#endif
