#ifdef TEST_BUILD

#include "Catch.h"
#include "math/functions/patterns/lines-pattern.h"
#include "math/approx.h"


using namespace math;

TEST_CASE("[Lines Pattern] 1/1/0")
{
    auto f = math::functions::patterns::lines(1, 1, 0_degrees);

    for (double x = -5.2; x < 7.4; x += 0.478)
    {
        CHECK(f(Point2D(x, -1.99)) == true);
        CHECK(f(Point2D(x, -1.01)) == true);
        CHECK(f(Point2D(x, -0.99)) == false);
        CHECK(f(Point2D(x, -0.01)) == false);
        CHECK(f(Point2D(x, 0.01)) == true);
        CHECK(f(Point2D(x, 0.99)) == true);
        CHECK(f(Point2D(x, 1.01)) == false);
        CHECK(f(Point2D(x, 1.99)) == false);
        CHECK(f(Point2D(x, 2.01)) == true);
        CHECK(f(Point2D(x, 2.99)) == true);
        CHECK(f(Point2D(x, 3.01)) == false);
        CHECK(f(Point2D(x, 3.99)) == false);
    }
}

TEST_CASE("[Lines Pattern] 2/2/0")
{
    auto f = math::functions::patterns::lines(2, 2, 0_degrees);

    for (double x = -5.2; x < 7.4; x += 0.478)
    {
        CHECK(f(Point2D(x, -2.01)) == true);
        CHECK(f(Point2D(x, -1.99)) == false);
        CHECK(f(Point2D(x, -1.01)) == false);
        CHECK(f(Point2D(x, -0.99)) == false);
        CHECK(f(Point2D(x, -0.01)) == false);
        CHECK(f(Point2D(x, 0.01)) == true);
        CHECK(f(Point2D(x, 0.99)) == true);
        CHECK(f(Point2D(x, 1.01)) == true);
        CHECK(f(Point2D(x, 1.99)) == true);
        CHECK(f(Point2D(x, 2.01)) == false);
        CHECK(f(Point2D(x, 2.99)) == false);
        CHECK(f(Point2D(x, 3.01)) == false);
        CHECK(f(Point2D(x, 3.99)) == false);
        CHECK(f(Point2D(x, 4.01)) == true);
    }
}

TEST_CASE("[Lines Pattern] 1/2/0")
{
    auto f = math::functions::patterns::lines(1, 2, 0_degrees);

    for (double x = -5.2; x < 7.4; x += 0.478)
    {
        CHECK(f(Point2D(x, -3.01)) == false);
        CHECK(f(Point2D(x, -2.99)) == true);
        CHECK(f(Point2D(x, -2.01)) == true);
        CHECK(f(Point2D(x, -1.99)) == false);
        CHECK(f(Point2D(x, -1.01)) == false);
        CHECK(f(Point2D(x, -0.99)) == false);
        CHECK(f(Point2D(x, -0.01)) == false);
        CHECK(f(Point2D(x, 0.01)) == true);
        CHECK(f(Point2D(x, 0.99)) == true);
        CHECK(f(Point2D(x, 1.01)) == false);
        CHECK(f(Point2D(x, 1.99)) == false);
        CHECK(f(Point2D(x, 2.01)) == false);
        CHECK(f(Point2D(x, 2.99)) == false);
        CHECK(f(Point2D(x, 3.01)) == true);
        CHECK(f(Point2D(x, 3.99)) == true);
        CHECK(f(Point2D(x, 4.01)) == false);
    }
}

TEST_CASE("[Lines Pattern] 1/2/90")
{
    auto f = math::functions::patterns::lines(1, 2, 90_degrees);

    for (double y = -5.2; y < 7.4; y += 0.478)
    {
        CHECK(f(Point2D(-3.01, y)) == true);
        CHECK(f(Point2D(-2.99, y)) == false);
        CHECK(f(Point2D(-2.01, y)) == false);
        CHECK(f(Point2D(-1.99, y)) == false);
        CHECK(f(Point2D(-1.01, y)) == false);
        CHECK(f(Point2D(-0.99, y)) == true);
        CHECK(f(Point2D(-0.01, y)) == true);
        CHECK(f(Point2D(0.01, y)) == false);
        CHECK(f(Point2D(0.99, y)) == false);
        CHECK(f(Point2D(1.01, y)) == false);
        CHECK(f(Point2D(1.99, y)) == false);
        CHECK(f(Point2D(2.01, y)) == true);
        CHECK(f(Point2D(2.99, y)) == true);
        CHECK(f(Point2D(3.01, y)) == false);
        CHECK(f(Point2D(3.99, y)) == false);
        CHECK(f(Point2D(4.01, y)) == false);
    }
}

#endif
