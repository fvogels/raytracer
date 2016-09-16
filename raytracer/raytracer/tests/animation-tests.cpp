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

        CHECK(anim(0_S) == Approx(0));
        CHECK(anim(0.5_S) == Approx(0.5));
        CHECK(anim(0.99999_S) == Approx(1));
    }

    SECTION("From 0 to 2 in 1s")
    {
        auto anim = animation::basic(0, 2, 1_s);

        CHECK(anim(0_S) == Approx(0));
        CHECK(anim(0.5_S) == Approx(1));
        CHECK(anim(0.999999_S) == Approx(2));
    }

    SECTION("From 1 to 3 in 1s")
    {
        auto anim = animation::basic(1, 3, 1_s);

        CHECK(anim(0_S) == Approx(1));
        CHECK(anim(0.5_S) == Approx(2));
        CHECK(anim(0.999999_S) == Approx(3));
    }

    SECTION("From 1 to 3 in 2s")
    {
        auto anim = animation::basic(1, 3, 2_s);

        CHECK(anim(0_S) == Approx(1));
        CHECK(anim(1_S) == Approx(2));
        CHECK(anim(1.999999_S) == Approx(3));
    }
}

TEST_CASE("[Animations] Easing double animation [0 -> 1: 1s] with bounce", "[Animations]")
{
    auto animation = animate(0.0, 1.0, 1_s);
    auto eased = ease(animation, math::functions::easing::bounce(3, 3));

    CHECK(eased(0_S) == approx(0.0));
    CHECK(eased(0.9999999999999_S) == approx(1.0));
}

TEST_CASE("[Animations] Easing double animation [0 -> 2: 1s] with bounce", "[Animations]")
{
    auto animation = animate(0.0, 2.0, 1_s);
    auto eased = ease(animation, math::functions::easing::bounce(3, 3));

    CHECK(eased(0_S) == approx(0.0));
    CHECK(eased(0.9999999999999_S) == approx(2.0));
}

TEST_CASE("[Animations] Easing double animation [1 -> 2: 1s] with bounce", "[Animations]")
{
    auto animation = animate(1.0, 2.0, 1_s);
    auto eased = ease(animation, math::functions::easing::bounce(3, 3));

    CHECK(eased(0_S) == approx(1.0));
    CHECK(eased(0.9999999999999_S) == approx(2.0));
}

TEST_CASE("[Animations] Easing double animation [1 -> 2: 2s] with bounce", "[Animations]")
{
    auto animation = animate(1.0, 2.0, 2_s);
    auto eased = ease(animation, math::functions::easing::bounce(3, 3));

    CHECK(eased(0_S) == approx(1.0));
    CHECK(eased(1.9999999999_S) == approx(2.0));
}

#endif
