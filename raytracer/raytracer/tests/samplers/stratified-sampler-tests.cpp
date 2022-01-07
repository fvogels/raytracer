#ifdef TEST_BUILD

#include "samplers/stratified-fixed-sampler.h"
#include "Catch.h"
#include <vector>
#include <limits>
#include <algorithm>

using namespace math;
using namespace raytracer;


#define P(x, y)(x, y)
#define V(x, y) (x, y)
#define Ps(...) __VA_ARGS__


#define TEST_SAMPLER(n, m, origin_, x_axis_, y_axis_, expected_)          \
    TEST_CASE("Stratified sampler " #origin_ " " #x_axis_ " " #y_axis_)   \
    {                                                                     \
        auto sampler = raytracer::samplers::stratified_fixed(n, m);       \
        Point2D origin origin_;                                           \
        Vector2D x_axis x_axis_;                                          \
        Vector2D y_axis y_axis_;                                          \
        Rectangle2D rectangle(origin, x_axis, y_axis);                    \
        auto pts = sampler->sample(rectangle);                            \
        auto expected = std::vector<Point2D>{ expected_ };                \
        CHECK(pts.size() == expected.size());                             \
        for (auto& p : expected)                                          \
        {                                                                 \
            bool found = false;                                           \
            for (auto& q : pts)                                           \
            {                                                             \
                if (p == approx(q))                                       \
                {                                                         \
                    found = true;                                         \
                }                                                         \
            }                                                             \
            CHECK(found);                                                 \
        }                                                                 \
    }

TEST_SAMPLER(1, 1, P(0.0, 0.0), V(1, 0), V(0, 1), Ps(Point2D(0.5, 0.5)));
TEST_SAMPLER(2, 2, P(0.0, 0.0), V(2, 0), V(0, 2), Ps(Point2D(0.5, 0.5), Point2D(1.5, 0.5), Point2D(0.5, 1.5), Point2D(1.5, 1.5)));

#endif
