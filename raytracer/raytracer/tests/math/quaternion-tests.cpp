#ifdef TEST_BUILD

#include "Catch.h"
#include "math/quaternion.h"

using namespace math;


#define Q(a, b, c, d)       (a, b, c, d)

#define TEST_ADDITION(q1, q2, qe)          \
    TEST_CASE("Addition of "#q1 " and " #q2 " should give " #qe)     \
    {                                          \
       Quaternion quat1 q1;                    \
       Quaternion quat2 q2;                    \
       Quaternion expected qe;                 \
       SECTION("Using operator +")             \
       {                                       \
           Quaternion actual = quat1 + quat2;  \
           CHECK(actual == expected);          \
       }                                       \
       SECTION("Using operator +=")            \
       {                                       \
           quat1 += quat2;                     \
           CHECK(quat1 == expected);           \
       }                                       \
    }

#define TEST_QQ_MULTIPLICATION(q1, q2, qe)     \
    TEST_CASE("Multiplication of "#q1 " and " #q2)     \
    {                                          \
       Quaternion quat1 q1;                    \
       Quaternion quat2 q2;                    \
       Quaternion expected qe;                 \
       Quaternion actual = quat1 * quat2;      \
       CHECK(actual == expected);              \
    }

#define AXIS(x, y, z)     (x, y, z)
#define POINT(x, y, z)    (x, y, z)

#define TEST_ROTATION(axis_, angle_, point_, expected_)                        \
    TEST_CASE("Rotation of " #point_ " by " #angle_ " degrees around " #axis_) \
    {                                                                          \
      Vector3D axis axis_;                                                     \
      Angle angle = Angle::degrees(angle_);                                    \
      Point3D point point_;                                                    \
      Point3D expected expected_;                                              \
      Quaternion quaternion = Quaternion::rotation(angle, axis);               \
      Point3D actual = quaternion.rotate(point);                               \
      CHECK(actual == approx(expected));                                       \
    }


TEST_ADDITION(Q(0, 0, 0, 0), Q(0, 0, 0, 0), Q(0, 0, 0, 0))
TEST_ADDITION(Q(1, 0, 0, 0), Q(0, 0, 0, 0), Q(1, 0, 0, 0))
TEST_ADDITION(Q(0, 0, 0, 0), Q(1, 0, 0, 0), Q(1, 0, 0, 0))
TEST_ADDITION(Q(1, 0, 0, 0), Q(1, 0, 0, 0), Q(2, 0, 0, 0))

TEST_QQ_MULTIPLICATION(Q(1, 0, 0, 0), Q(1, 0, 0, 0), Q(1, 0, 0, 0))
TEST_QQ_MULTIPLICATION(Q(1, 0, 0, 0), Q(0, 1, 0, 0), Q(0, 1, 0, 0))
TEST_QQ_MULTIPLICATION(Q(1, 0, 0, 0), Q(0, 0, 1, 0), Q(0, 0, 1, 0))
TEST_QQ_MULTIPLICATION(Q(1, 0, 0, 0), Q(0, 0, 0, 1), Q(0, 0, 0, 1))
TEST_QQ_MULTIPLICATION(Q(0, 1, 0, 0), Q(0, 1, 0, 0), Q(-1, 0, 0, 0))
TEST_QQ_MULTIPLICATION(Q(0, 1, 0, 0), Q(0, 0, 1, 0), Q(0, 0, 0, 1))
TEST_QQ_MULTIPLICATION(Q(0, 1, 0, 0), Q(0, 0, 0, 1), Q(0, 0, -1, 0))

TEST_ROTATION(AXIS(0, 1, 0), 0, POINT(0, 0, 0), POINT(0, 0, 0))
TEST_ROTATION(AXIS(0, 1, 0), 0, POINT(1, 0, 0), POINT(1, 0, 0))
TEST_ROTATION(AXIS(0, 1, 0), 0, POINT(0, 1, 0), POINT(0, 1, 0))
TEST_ROTATION(AXIS(0, 1, 0), 0, POINT(0, 0, 1), POINT(0, 0, 1))
TEST_ROTATION(AXIS(0, 1, 0), 90, POINT(0, 0, 0), POINT(0, 0, 0))
TEST_ROTATION(AXIS(0, 1, 0), 90, POINT(1, 0, 0), POINT(0, 0, -1))
TEST_ROTATION(AXIS(0, 1, 0), -90, POINT(1, 0, 0), POINT(0, 0, 1))
TEST_ROTATION(AXIS(0, 1, 0), 180, POINT(1, 0, 0), POINT(-1, 0, 0))
TEST_ROTATION(AXIS(0, 1, 0), 360, POINT(1, 0, 0), POINT(1, 0, 0))
TEST_ROTATION(AXIS(1, 0, 0), 90, POINT(1, 0, 0), POINT(1, 0, 0))
TEST_ROTATION(AXIS(1, 0, 0), 90, POINT(0, 1, 0), POINT(0, 0, 1))
TEST_ROTATION(AXIS(1, 0, 0), -90, POINT(0, 1, 0), POINT(0, 0, -1))
TEST_ROTATION(AXIS(1, 0, 0), 180, POINT(0, 1, 0), POINT(0, -1, 0))
TEST_ROTATION(AXIS(0, 0, 1), 90, POINT(1, 0, 0), POINT(0, 1, 0))
TEST_ROTATION(AXIS(0, 0, 1), -90, POINT(1, 0, 0), POINT(0, -1, 0))
TEST_ROTATION(AXIS(0, 0, 1), 180, POINT(1, 0, 0), POINT(-1, 0, 0))

#endif
