#ifdef TEST_BUILD

#include "Catch.h"
#include "animation/animations.h"
#include "animation/time-stamp.h"

using namespace math;
using namespace animation;


TEST_CASE("[Animations] basic", "[Animations]")
{
    SECTION("From 0 to 1 in 1s")
    {
        auto anim = animation::basic(0, 1, 1_s);
        auto ts = 0_S;

        CHECK(anim(0_S) == Approx(0));
        CHECK(anim(0.5_S) == Approx(0.5));
        CHECK(anim(1_S) == Approx(1));
    }

    SECTION("From 0 to 2 in 1s")
    {
        auto anim = animation::basic(0, 2, 1_s);
        auto ts = 0_S;

        CHECK(anim(0_S) == Approx(0));
        CHECK(anim(0.5_S) == Approx(1));
        CHECK(anim(1_S) == Approx(2));
    }

    SECTION("From 1 to 3 in 1s")
    {
        auto anim = animation::basic(1, 3, 1_s);
        auto ts = 0_S;

        CHECK(anim(0_S) == Approx(1));
        CHECK(anim(0.5_S) == Approx(2));
        CHECK(anim(1_S) == Approx(3));
    }
}

#endif
