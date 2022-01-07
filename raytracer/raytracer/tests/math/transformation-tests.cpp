#ifdef TEST_BUILD

#include "Catch.h"
#include "math/transformation2d.h"
#include "math/transformation3d.h"

using namespace math;



#define V(...) (__VA_ARGS__)
#define P(...) (__VA_ARGS__)

#define TEST_TRANSLATION2D(v, p, q)                                      \
    TEST_CASE("Translation by " #v " of " #p " should yield " #q)        \
    {                                                                    \
        auto transformation = transformations::translation(Vector2D v);  \
        auto original = Point2D p;                                       \
        auto transformed = Point2D q;                                    \
        auto& m = transformation.transformation_matrix;                  \
        auto& im = transformation.inverse_transformation_matrix;         \
                                                                         \
        CHECK(m * original == approx(transformed));                      \
        CHECK(im * transformed == approx(original));                     \
    }

TEST_TRANSLATION2D(V(1, 0), P(2, 3), P(3, 3))
TEST_TRANSLATION2D(V(4, 1), P(2, 3), P(6, 4))


TEST_CASE("[Transformation] rotate_align_y", "[Transformation]")
{
    SECTION("y_axis = (0,1,0)")
    {
        Vector3D y_axis(0, 1, 0);

        auto transformation = transformations::rotate_align_y(y_axis);

        auto transformed = transformation.transformation_matrix * Vector3D(0, 1, 0);
        CHECK(transformed == approx(y_axis));
    }

    SECTION("y_axis = (1,1,0)")
    {
        Vector3D y_axis = Vector3D(1, 1, 0).normalized();

        auto transformation = transformations::rotate_align_y(y_axis);

        auto transformed = transformation.transformation_matrix * Vector3D(0, 1, 0);
        CHECK(transformed == approx(y_axis));
    }

    SECTION("y_axis = (1,1,1)")
    {
        Vector3D y_axis = Vector3D(1, 1, 1).normalized();

        auto transformation = transformations::rotate_align_y(y_axis);

        auto transformed = transformation.transformation_matrix * Vector3D(0, 1, 0);
        CHECK(transformed == approx(y_axis));
    }

    SECTION("y_axis = (1,-1,1)")
    {
        Vector3D y_axis = Vector3D(1, -1, 1).normalized();

        auto transformation = transformations::rotate_align_y(y_axis);

        auto transformed = transformation.transformation_matrix * Vector3D(0, 1, 0);
        CHECK(transformed == approx(y_axis));
    }

    for (double x = -1; x <= 1; x += 0.25)
    {
        for (double y = -1; y <= 1; y += 0.25)
        {
            for (double z = -1; z <= 1; z += 0.25)
            {
                if (x != 0 || y != 0 || z != 0)
                {
                    Vector3D y_axis = Vector3D(x, y, z).normalized();

                    auto transformation = transformations::rotate_align_y(y_axis);

                    auto transformed = transformation.transformation_matrix * Vector3D(0, 1, 0);
                    CHECK(transformed == approx(y_axis));
                }
            }
        }
    }
}

#endif
