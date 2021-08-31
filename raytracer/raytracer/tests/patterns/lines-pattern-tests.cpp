#ifdef TEST_BUILD

#include "Catch.h"
#include "patterns/lines-pattern.h"
#include "math/approx.h"


using namespace math;

TEST_CASE("[Lines Pattern] 1/1")
{
    auto f = math::functions::patterns::lines(1, 1);

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

TEST_CASE("[Lines Pattern] 2/2")
{
    auto f = math::functions::patterns::lines(2, 2);

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

TEST_CASE("[Lines Pattern] 1/2")
{
    auto f = math::functions::patterns::lines(1, 2);

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

#endif
