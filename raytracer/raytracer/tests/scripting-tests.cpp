#ifdef TEST_BUILD

#include "Catch.h"
#include "chai/scripting.h"
#include "math/vector3d.h"
#include "math/point3d.h"
#include "math/approx.h"
#include "imaging/color.h"
#include "raytracing/scene.h"
#include <sstream>

using namespace raytracer::scripting;


//TEST_CASE("[Scripting] Creation of a vector", "[Scripting]")
//{
//    auto result = evaluate<math::Vector3D>("vec(1,2,3)");
//
//    REQUIRE(result == math::approx(math::Vector3D(1, 2, 3)));
//}
//
//TEST_CASE("[Scripting] Creation of a point", "[Scripting]")
//{
//    auto result = evaluate<math::Point3D>("pos(1,2,3)");
//
//    REQUIRE(result == math::approx(math::Point3D(1, 2, 3)));
//}
//
//TEST_CASE("[Scripting] Vector addition", "[Scripting]")
//{
//    auto result = evaluate<math::Vector3D>("vec(1,2,3) + vec(4,5,6)");
//
//    REQUIRE(result == math::approx(math::Vector3D(5, 7, 9)));
//}
//
//TEST_CASE("[Scripting] Vector + Point", "[Scripting]")
//{
//    auto result = evaluate<math::Point3D>("pos(1,2,3) + vec(4,5,6)");
//
//    REQUIRE(result == math::approx(math::Point3D(5, 7, 9)));
//}
//
//TEST_CASE("[Scripting] Point + Vector", "[Scripting]")
//{
//    auto result = evaluate<math::Point3D>("vec(1,2,3) + pos(4,5,6)");
//
//    REQUIRE(result == math::approx(math::Point3D(5, 7, 9)));
//}
//
//TEST_CASE("[Scripting] colors.black()", "[Scripting]")
//{
//    auto result = evaluate<imaging::color>("colors.black()");
//
//    REQUIRE(result == math::approx(imaging::colors::black()));
//}
//
//TEST_CASE("[Scripting] colors.white()", "[Scripting]")
//{
//    auto result = evaluate<imaging::color>("colors.white()");
//
//    REQUIRE(result == math::approx(imaging::colors::white()));
//}
//
//TEST_CASE("[Scripting] colors.red()", "[Scripting]")
//{
//    auto result = evaluate<imaging::color>("colors.red()");
//
//    REQUIRE(result == math::approx(imaging::colors::red()));
//}
//
//TEST_CASE("[Scripting] colors.blue() * 0.5", "[Scripting]")
//{
//    auto result = evaluate<imaging::color>("colors.blue() * 0.5");
//
//    REQUIRE(result == math::approx(imaging::colors::blue() * 0.5));
//}

TEST_CASE("[Scripting] Creating perspective camera", "[Scripting]")
{
    // 
    auto result = evaluate<raytracer::Camera>(R"(
        var camera = cameras.perspective(pos(0,0,5), pos(0,0,0), vec(0,1,0), 1, 1)
        camera
    )");

    REQUIRE(!!result);
}

//TEST_CASE("[Scripting] Adding light to scene", "[Scripting]")
//{
//    auto result = evaluate<raytracer::Scene>(R"(
//        var scene = Scene()
//        scene.lights = [ omnidirectional( pos(0,0,0), colors.white() ) ]
//        scene
//    )");
//
//    REQUIRE(result.light_sources.size() == 1);
//}

#endif
