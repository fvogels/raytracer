#ifdef TEST_BUILD

#include "Catch.h"
#include "math/interval.h"
#include "math/angle.h"
#include "math/point.h"
#include "animation/time-stamp.h"

using namespace math;
using namespace animation;


TEST_CASE("[Interval] Interval<double>::from_relative", "[Interval]")
{
    auto i = interval(1.0, 5.0);

    CHECK(i.from_relative(0) == Approx(1));
    CHECK(i.from_relative(0.5) == Approx(3));
    CHECK(i.from_relative(1) == Approx(5));
}

TEST_CASE("[Interval] Interval<Angle>::from_relative", "[Interval]")
{
    auto i = interval(60_degrees, 180_degrees);

    CHECK(i.from_relative(0) == approx(60_degrees));
    CHECK(i.from_relative(0.5) == approx(120_degrees));
    CHECK(i.from_relative(1) == approx(180_degrees));
}

TEST_CASE("[Interval] Interval<Point3D>::from_relative", "[Interval]")
{
    auto i = interval(Point3D(1, 2, 3), Point3D(5, 8, 9));

    CHECK(i.from_relative(0) == approx(Point3D(1, 2, 3)));
    CHECK(i.from_relative(0.5) == approx(Point3D(3, 5, 6)));
    CHECK(i.from_relative(1) == approx(Point3D(5, 8, 9)));
}

TEST_CASE("[Interval] Interval<TimeStamp>::from_relative", "[Interval]")
{
    auto i = interval(TimeStamp::from_epoch(1_s), TimeStamp::from_epoch(5_s));

    CHECK(i.from_relative(0) == approx(TimeStamp::from_epoch(1_s)));
    CHECK(i.from_relative(0.5) == approx(TimeStamp::from_epoch(3_s)));
    CHECK(i.from_relative(1) == approx(TimeStamp::from_epoch(5_s)));
}

#endif
