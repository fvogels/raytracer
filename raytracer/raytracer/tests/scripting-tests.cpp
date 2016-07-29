#ifdef TEST_BUILD

#include "Catch.h"
#include "scripting/scripting.h"
#include "math/vector3d.h"
#include "math/point3d.h"
#include "math/approx.h"
#include "imaging/Color.h"
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
//    auto result = evaluate<imaging::Color>("Colors.black()");
//
//    REQUIRE(result == math::approx(imaging::colors::black()));
//}
//
//TEST_CASE("[Scripting] colors.white()", "[Scripting]")
//{
//    auto result = evaluate<imaging::Color>("Colors.white()");
//
//    REQUIRE(result == math::approx(imaging::colors::white()));
//}
//
//TEST_CASE("[Scripting] colors.red()", "[Scripting]")
//{
//    auto result = evaluate<imaging::Color>("Colors.red()");
//
//    REQUIRE(result == math::approx(imaging::colors::red()));
//}
//
//TEST_CASE("[Scripting] colors.blue() * 0.5", "[Scripting]")
//{
//    auto result = evaluate<imaging::Color>("Colors.blue() * 0.5");
//
//    REQUIRE(result == math::approx(imaging::colors::blue() * 0.5));
//}
//
//TEST_CASE("[Scripting] Creating perspective camera", "[Scripting]")
//{
//    auto result = evaluate<raytracer::Camera>(R"(
//        var camera = Cameras.perspective(pos(0,0,5), pos(0,0,0), vec(0,1,0), 1, 1)
//        camera
//    )");
//
//    REQUIRE(!!result);
//}
//
TEST_CASE("[Scripting] Creating perspective camera using argument map", "[Scripting]")
{
    auto result = evaluate<raytracer::Camera>(R"(
        Cameras.perspective(["eye": pos(0,0,5), "look_at": pos(0,0,0), "up": vec(0,1,0), "distance": 1, "aspect_ratio": 1])
    )");

    REQUIRE(!!result);
}

TEST_CASE("[Scripting] Testing pipeline", "[Scripting]")
{
    evaluate<void>(R"(
        var camera     = Cameras.perspective(pos(0,0,5), pos(0,0,0), vec(0,1,0), 1, 1)
        var material   = Materials.uniform( Colors.white() * 0.2,
                                            Colors.white() * 0.8,
                                            Colors.white(),
                                            20,
                                            0.2,
                                            0,
                                            0 )
        var root       = Primitives.decorate( material, Primitives.sphere() )
        var lights     = [ Lights.omnidirectional(pos(0,5,0), Colors.white()) ]
        var scene      = scene(camera, root, lights )
        var ray_tracer = Raytracers.binary()
        var renderer   = Renderers.standard(500, 500, Samplers.single(), ray_tracer)
        pipeline(scene, [ Pipeline.renderer(renderer)
                        , Pipeline.wif("e:/temp/output/test.wif") ])
    )");
}


//
//TEST_CASE("[Scripting] Adding light to scene", "[Scripting]")
//{
//    auto result = evaluate<raytracer::Scene>(R"(
//        var camera = Cameras.perspective(pos(0,0,5), pos(0,0,0), vec(0,1,0), 1, 1)
//        var root   = sphere()
//        var scene  = Scene(camera, root)
//
//        add_light( scene, Lights.omnidirectional(pos(0,5,0), Colors.white()) )
//
//        scene
//    )");
//
//    REQUIRE(result.light_sources.size() == 1);
//}

#endif
