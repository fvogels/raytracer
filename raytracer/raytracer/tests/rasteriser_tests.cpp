#ifdef TEST_BUILD

#include "math/rasteriser.h"
#include "Catch.h"

using namespace math;

TEST_CASE("Rasterising [0,1]-[1,0] in 2x2", "[rasteriser]")
{
	rectangle2d rect(point2d(0, 1), vector2d(1, 0), vector2d(0, -1));
	rasteriser r(rect, 2, 2);
	
	REQUIRE(r[position(0, 0)] == rectangle2d(point2d(0, 1), vector2d(0.5, 0), vector2d(0, -0.5)));
	REQUIRE(r[position(1, 0)] == rectangle2d(point2d(0.5, 1), vector2d(0.5, 0), vector2d(0, -0.5)));
	REQUIRE(r[position(0, 1)] == rectangle2d(point2d(0, 0.5), vector2d(0.5, 0), vector2d(0, -0.5)));
	REQUIRE(r[position(1, 1)] == rectangle2d(point2d(0.5, 0.5), vector2d(0.5, 0), vector2d(0, -0.5)));
}

#endif
