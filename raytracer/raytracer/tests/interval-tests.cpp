#ifdef TEST_BUILD

#include "Catch.h"
#include "math/interval.h"
#include "math/angle.h"
#include "math/point.h"
#include "math/approx.h"

using namespace math;


TEST_CASE("[Interval] interval(0.0, 1.0).from_relative(0.0)", "[Interval]")
{
    auto i = interval(0.0, 1.0);
    auto t = 0.0;
    auto actual = i.from_relative(t);
    auto expected = 0.0;

    REQUIRE(actual == approx(expected));
}

TEST_CASE("[Interval] interval(0.0, 1.0).to_relative(0.0)", "[Interval]")
{
    auto i = interval(0.0, 1.0);
    auto x = 0.0;
    auto actual = i.to_relative(x);
    auto expected = 0.0;

    REQUIRE(actual == approx(expected));
}

TEST_CASE("[Interval] interval(0.0, 1.0).from_relative(1.0)", "[Interval]")
{
    auto i = interval(0.0, 1.0);
    auto t = 1.0;
    auto actual = i.from_relative(t);
    auto expected = 1.0;

    REQUIRE(actual == approx(expected));
}

TEST_CASE("[Interval] interval(0.0, 1.0).to_relative(1.0)", "[Interval]")
{
    auto i = interval(0.0, 1.0);
    auto x = 1.0;
    auto actual = i.to_relative(x);
    auto expected = 1.0;

    REQUIRE(actual == approx(expected));
}

TEST_CASE("[Interval] interval(0.0, 1.0).from_relative(0.5)", "[Interval]")
{
    auto i = interval(0.0, 1.0);
    auto t = 0.5;
    auto actual = i.from_relative(t);
    auto expected = 0.5;

    REQUIRE(actual == approx(expected));
}

TEST_CASE("[Interval] interval(0.0, 1.0).to_relative(0.5)", "[Interval]")
{
    auto i = interval(0.0, 1.0);
    auto x = 0.5;
    auto actual = i.to_relative(x);
    auto expected = 0.5;

    REQUIRE(actual == approx(expected));
}

TEST_CASE("[Interval] interval(0.0, 2.0).from_relative(0.0)", "[Interval]")
{
    auto i = interval(0.0, 2.0);
    auto t = 0.0;
    auto actual = i.from_relative(t);
    auto expected = 0.0;

    REQUIRE(actual == approx(expected));
}

TEST_CASE("[Interval] interval(0.0, 2.0).to_relative(0.0)", "[Interval]")
{
    auto i = interval(0.0, 2.0);
    auto x = 0.0;
    auto actual = i.to_relative(x);
    auto expected = 0.0;

    REQUIRE(actual == approx(expected));
}

TEST_CASE("[Interval] interval(0.0, 2.0).from_relative(1.0)", "[Interval]")
{
    auto i = interval(0.0, 2.0);
    auto t = 1.0;
    auto actual = i.from_relative(t);
    auto expected = 2.0;

    REQUIRE(actual == approx(expected));
}

TEST_CASE("[Interval] interval(0.0, 2.0).to_relative(2.0)", "[Interval]")
{
    auto i = interval(0.0, 2.0);
    auto x = 2.0;
    auto actual = i.to_relative(x);
    auto expected = 1.0;

    REQUIRE(actual == approx(expected));
}

TEST_CASE("[Interval] interval(0.0, 2.0).from_relative(0.5)", "[Interval]")
{
    auto i = interval(0.0, 2.0);
    auto t = 0.5;
    auto actual = i.from_relative(t);
    auto expected = 1.0;

    REQUIRE(actual == approx(expected));
}

TEST_CASE("[Interval] interval(0.0, 2.0).to_relative(1.0)", "[Interval]")
{
    auto i = interval(0.0, 2.0);
    auto x = 1.0;
    auto actual = i.to_relative(x);
    auto expected = 0.5;

    REQUIRE(actual == approx(expected));
}

TEST_CASE("[Interval] interval(1.0, 3.0).from_relative(0.0)", "[Interval]")
{
    auto i = interval(1.0, 3.0);
    auto t = 0.0;
    auto actual = i.from_relative(t);
    auto expected = 1.0;

    REQUIRE(actual == approx(expected));
}

TEST_CASE("[Interval] interval(1.0, 3.0).to_relative(1.0)", "[Interval]")
{
    auto i = interval(1.0, 3.0);
    auto x = 1.0;
    auto actual = i.to_relative(x);
    auto expected = 0.0;

    REQUIRE(actual == approx(expected));
}

TEST_CASE("[Interval] interval(1.0, 3.0).from_relative(1.0)", "[Interval]")
{
    auto i = interval(1.0, 3.0);
    auto t = 1.0;
    auto actual = i.from_relative(t);
    auto expected = 3.0;

    REQUIRE(actual == approx(expected));
}

TEST_CASE("[Interval] interval(1.0, 3.0).to_relative(3.0)", "[Interval]")
{
    auto i = interval(1.0, 3.0);
    auto x = 3.0;
    auto actual = i.to_relative(x);
    auto expected = 1.0;

    REQUIRE(actual == approx(expected));
}

TEST_CASE("[Interval] interval(1.0, 3.0).from_relative(0.5)", "[Interval]")
{
    auto i = interval(1.0, 3.0);
    auto t = 0.5;
    auto actual = i.from_relative(t);
    auto expected = 2.0;

    REQUIRE(actual == approx(expected));
}

TEST_CASE("[Interval] interval(1.0, 3.0).to_relative(2.0)", "[Interval]")
{
    auto i = interval(1.0, 3.0);
    auto x = 2.0;
    auto actual = i.to_relative(x);
    auto expected = 0.5;

    REQUIRE(actual == approx(expected));
}

TEST_CASE("[Interval] Interval<double>::empty().intersect(Interval<double>::empty())", "[Interval]")
{
    auto i1 = Interval<double>::empty();
    auto i2 = Interval<double>::empty();
    auto expected = Interval<double>::empty();
    auto actual = i1.intersect(i2);

    REQUIRE(actual.lower == approx(expected.lower));
    REQUIRE(actual.upper == approx(expected.upper));
}

TEST_CASE("[Interval] Interval<double>::empty().intersect(interval(0.0, 1.0))", "[Interval]")
{
    auto i1 = Interval<double>::empty();
    auto i2 = interval(0.0, 1.0);
    auto expected = Interval<double>::empty();
    auto actual = i1.intersect(i2);

    REQUIRE(actual.lower == approx(expected.lower));
    REQUIRE(actual.upper == approx(expected.upper));
}

TEST_CASE("[Interval] Interval<double>::empty().intersect(interval(-1.0, 1.0))", "[Interval]")
{
    auto i1 = Interval<double>::empty();
    auto i2 = interval(-1.0, 1.0);
    auto expected = Interval<double>::empty();
    auto actual = i1.intersect(i2);

    REQUIRE(actual.lower == approx(expected.lower));
    REQUIRE(actual.upper == approx(expected.upper));
}

TEST_CASE("[Interval] interval(0.0, 1.0).intersect(Interval<double>::empty())", "[Interval]")
{
    auto i1 = interval(0.0, 1.0);
    auto i2 = Interval<double>::empty();
    auto expected = Interval<double>::empty();
    auto actual = i1.intersect(i2);

    REQUIRE(actual.lower == approx(expected.lower));
    REQUIRE(actual.upper == approx(expected.upper));
}

TEST_CASE("[Interval] interval(0.0, 5.0).intersect(Interval<double>::empty())", "[Interval]")
{
    auto i1 = interval(0.0, 5.0);
    auto i2 = Interval<double>::empty();
    auto expected = Interval<double>::empty();
    auto actual = i1.intersect(i2);

    REQUIRE(actual.lower == approx(expected.lower));
    REQUIRE(actual.upper == approx(expected.upper));
}

TEST_CASE("[Interval] Interval<double>::infinite().intersect(interval(0.0, 1.0))", "[Interval]")
{
    auto i1 = Interval<double>::infinite();
    auto i2 = interval(0.0, 1.0);
    auto expected = interval(0.0, 1.0);
    auto actual = i1.intersect(i2);

    REQUIRE(actual.lower == approx(expected.lower));
    REQUIRE(actual.upper == approx(expected.upper));
}

TEST_CASE("[Interval] Interval<double>::infinite().intersect(Interval<double>::infinite())", "[Interval]")
{
    auto i1 = Interval<double>::infinite();
    auto i2 = Interval<double>::infinite();
    auto expected = Interval<double>::infinite();
    auto actual = i1.intersect(i2);

    REQUIRE(actual.lower == approx(expected.lower));
    REQUIRE(actual.upper == approx(expected.upper));
}

TEST_CASE("[Interval] Interval<double>::infinite().intersect(Interval<double>::empty())", "[Interval]")
{
    auto i1 = Interval<double>::infinite();
    auto i2 = Interval<double>::empty();
    auto expected = Interval<double>::empty();
    auto actual = i1.intersect(i2);

    REQUIRE(actual.lower == approx(expected.lower));
    REQUIRE(actual.upper == approx(expected.upper));
}

TEST_CASE("[Interval] Interval<double>::empty().intersect(Interval<double>::infinite())", "[Interval]")
{
    auto i1 = Interval<double>::empty();
    auto i2 = Interval<double>::infinite();
    auto expected = Interval<double>::empty();
    auto actual = i1.intersect(i2);

    REQUIRE(actual.lower == approx(expected.lower));
    REQUIRE(actual.upper == approx(expected.upper));
}

TEST_CASE("[Interval] interval(0.0, 1.0).intersect(interval(0.0, 1.0))", "[Interval]")
{
    auto i1 = interval(0.0, 1.0);
    auto i2 = interval(0.0, 1.0);
    auto expected = interval(0.0, 1.0);
    auto actual = i1.intersect(i2);

    REQUIRE(actual.lower == approx(expected.lower));
    REQUIRE(actual.upper == approx(expected.upper));
}

TEST_CASE("[Interval] interval(0.0, 1.0).intersect(interval(0.0, 2.0))", "[Interval]")
{
    auto i1 = interval(0.0, 1.0);
    auto i2 = interval(0.0, 2.0);
    auto expected = interval(0.0, 1.0);
    auto actual = i1.intersect(i2);

    REQUIRE(actual.lower == approx(expected.lower));
    REQUIRE(actual.upper == approx(expected.upper));
}

TEST_CASE("[Interval] interval(0.0, 1.0).intersect(interval(-1.0, 2.0))", "[Interval]")
{
    auto i1 = interval(0.0, 1.0);
    auto i2 = interval(-1.0, 2.0);
    auto expected = interval(0.0, 1.0);
    auto actual = i1.intersect(i2);

    REQUIRE(actual.lower == approx(expected.lower));
    REQUIRE(actual.upper == approx(expected.upper));
}

TEST_CASE("[Interval] interval(-1.0, 1.0).intersect(interval(0.0, 1.0))", "[Interval]")
{
    auto i1 = interval(-1.0, 1.0);
    auto i2 = interval(0.0, 1.0);
    auto expected = interval(0.0, 1.0);
    auto actual = i1.intersect(i2);

    REQUIRE(actual.lower == approx(expected.lower));
    REQUIRE(actual.upper == approx(expected.upper));
}

TEST_CASE("[Interval] interval(0.0, 2.0).intersect(interval(0.0, 1.0))", "[Interval]")
{
    auto i1 = interval(0.0, 2.0);
    auto i2 = interval(0.0, 1.0);
    auto expected = interval(0.0, 1.0);
    auto actual = i1.intersect(i2);

    REQUIRE(actual.lower == approx(expected.lower));
    REQUIRE(actual.upper == approx(expected.upper));
}

TEST_CASE("[Interval] interval(0.0, 2.0).intersect(interval(0.0, 3.0))", "[Interval]")
{
    auto i1 = interval(0.0, 2.0);
    auto i2 = interval(0.0, 3.0);
    auto expected = interval(0.0, 2.0);
    auto actual = i1.intersect(i2);

    REQUIRE(actual.lower == approx(expected.lower));
    REQUIRE(actual.upper == approx(expected.upper));
}

TEST_CASE("[Interval] interval(-1.0, 2.0).intersect(interval(0.0, 3.0))", "[Interval]")
{
    auto i1 = interval(-1.0, 2.0);
    auto i2 = interval(0.0, 3.0);
    auto expected = interval(0.0, 2.0);
    auto actual = i1.intersect(i2);

    REQUIRE(actual.lower == approx(expected.lower));
    REQUIRE(actual.upper == approx(expected.upper));
}

TEST_CASE("[Interval] interval(-1.0, 2.0).intersect(interval(-2.0, 1.0))", "[Interval]")
{
    auto i1 = interval(-1.0, 2.0);
    auto i2 = interval(-2.0, 1.0);
    auto expected = interval(-1.0, 1.0);
    auto actual = i1.intersect(i2);

    REQUIRE(actual.lower == approx(expected.lower));
    REQUIRE(actual.upper == approx(expected.upper));
}

TEST_CASE("[Interval] interval(0.0, 1.0).merge(interval(0.0, 1.0))", "[Interval]")
{
    auto i1 = interval(0.0, 1.0);
    auto i2 = interval(0.0, 1.0);
    auto expected = interval(0.0, 1.0);
    auto actual = i1.merge(i2);

    REQUIRE(actual.lower == approx(expected.lower));
    REQUIRE(actual.upper == approx(expected.upper));
}

TEST_CASE("[Interval] interval(0.0, 1.0).merge(interval(1.0, 2.0))", "[Interval]")
{
    auto i1 = interval(0.0, 1.0);
    auto i2 = interval(1.0, 2.0);
    auto expected = interval(0.0, 2.0);
    auto actual = i1.merge(i2);

    REQUIRE(actual.lower == approx(expected.lower));
    REQUIRE(actual.upper == approx(expected.upper));
}

TEST_CASE("[Interval] interval(0.0, 1.0).merge(interval(2.0, 3.0))", "[Interval]")
{
    auto i1 = interval(0.0, 1.0);
    auto i2 = interval(2.0, 3.0);
    auto expected = interval(0.0, 3.0);
    auto actual = i1.merge(i2);

    REQUIRE(actual.lower == approx(expected.lower));
    REQUIRE(actual.upper == approx(expected.upper));
}

TEST_CASE("[Interval] Interval<double>::empty().merge(Interval<double>::empty())", "[Interval]")
{
    auto i1 = Interval<double>::empty();
    auto i2 = Interval<double>::empty();
    auto expected = Interval<double>::empty();
    auto actual = i1.merge(i2);

    REQUIRE(actual.lower == approx(expected.lower));
    REQUIRE(actual.upper == approx(expected.upper));
}

TEST_CASE("[Interval] Interval<double>::empty().merge(interval(0.0, 1.0))", "[Interval]")
{
    auto i1 = Interval<double>::empty();
    auto i2 = interval(0.0, 1.0);
    auto expected = interval(0.0, 1.0);
    auto actual = i1.merge(i2);

    REQUIRE(actual.lower == approx(expected.lower));
    REQUIRE(actual.upper == approx(expected.upper));
}

TEST_CASE("[Interval] interval(0.0, 1.0).merge(Interval<double>::empty())", "[Interval]")
{
    auto i1 = interval(0.0, 1.0);
    auto i2 = Interval<double>::empty();
    auto expected = interval(0.0, 1.0);
    auto actual = i1.merge(i2);

    REQUIRE(actual.lower == approx(expected.lower));
    REQUIRE(actual.upper == approx(expected.upper));
}

TEST_CASE("[Interval] Interval<double>::infinite().merge(interval(0.0, 1.0))", "[Interval]")
{
    auto i1 = Interval<double>::infinite();
    auto i2 = interval(0.0, 1.0);
    auto expected = Interval<double>::infinite();
    auto actual = i1.merge(i2);

    REQUIRE(actual.lower == approx(expected.lower));
    REQUIRE(actual.upper == approx(expected.upper));
}

TEST_CASE("[Interval] interval(0.0, 1.0).merge(Interval<double>::infinite())", "[Interval]")
{
    auto i1 = interval(0.0, 1.0);
    auto i2 = Interval<double>::infinite();
    auto expected = Interval<double>::infinite();
    auto actual = i1.merge(i2);

    REQUIRE(actual.lower == approx(expected.lower));
    REQUIRE(actual.upper == approx(expected.upper));
}

TEST_CASE("[Interval] Interval<double>::infinite().merge(Interval<double>::empty())", "[Interval]")
{
    auto i1 = Interval<double>::infinite();
    auto i2 = Interval<double>::empty();
    auto expected = Interval<double>::infinite();
    auto actual = i1.merge(i2);

    REQUIRE(actual.lower == approx(expected.lower));
    REQUIRE(actual.upper == approx(expected.upper));
}

TEST_CASE("[Interval] Interval<double>::empty().merge(Interval<double>::infinite())", "[Interval]")
{
    auto i1 = Interval<double>::empty();
    auto i2 = Interval<double>::infinite();
    auto expected = Interval<double>::infinite();
    auto actual = i1.merge(i2);

    REQUIRE(actual.lower == approx(expected.lower));
    REQUIRE(actual.upper == approx(expected.upper));
}

#endif
