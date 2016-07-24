#ifdef TEST_BUILD

#include "math/rasterizer.h"
#include "Catch.h"

using namespace math;

TEST_CASE("Rasterising [0,1]-[1,0] in 2x2", "[Rasterizer]")
{
    Rectangle2D rect(point(0, 1), vector(1, 0), vector(0, -1));
    Rasterizer r(rect, 2, 2);
    
    REQUIRE(r[Position(0, 0)] == Rectangle2D(point(0, 1), vector(0.5, 0), vector(0, -0.5)));
    REQUIRE(r[Position(1, 0)] == Rectangle2D(point(0.5, 1), vector(0.5, 0), vector(0, -0.5)));
    REQUIRE(r[Position(0, 1)] == Rectangle2D(point(0, 0.5), vector(0.5, 0), vector(0, -0.5)));
    REQUIRE(r[Position(1, 1)] == Rectangle2D(point(0.5, 0.5), vector(0.5, 0), vector(0, -0.5)));
}

#endif
