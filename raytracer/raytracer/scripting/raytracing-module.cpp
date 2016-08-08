#include "scripting/raytracing-module.h"
#include "raytracing/ray-tracers.h"
#include "scripting/scripting-util.h"

using namespace chaiscript;
using namespace raytracer;
using namespace raytracer::scripting;


namespace
{
    struct RaytracerLibrary
    {
        RayTracer binary() const { return raytracer::raytracers::binary(); }
        RayTracer v1() const { return raytracer::raytracers::v1(); }
        RayTracer v2() const { return raytracer::raytracers::v2(); }
        RayTracer v3() const { return raytracer::raytracers::v3(); }
        RayTracer v4() const { return raytracer::raytracers::v4(); }
        RayTracer v5() const { return raytracer::raytracers::v5(); }
        RayTracer v6() const { return raytracer::raytracers::v6(); }
    };

    std::shared_ptr<Scene> create_scene(Camera camera, Primitive root, const std::vector<Boxed_Value>& boxed_lights)
    {
        auto unboxed_lights = util::cast_vector_elements<LightSource>(boxed_lights);
        return std::make_shared<Scene>(camera, root, unboxed_lights);
    }
}

ModulePtr raytracer::scripting::_private_::create_raytracing_module()
{
    auto module = std::make_shared<chaiscript::Module>();

    auto raytracer_library = std::make_shared<RaytracerLibrary>();
    module->add_global_const(chaiscript::const_var(raytracer_library), "Raytracers");

#define RAYTRACER(NAME) module->add(fun(&RaytracerLibrary::NAME), #NAME)
    RAYTRACER(binary);
    RAYTRACER(v1);
    RAYTRACER(v2);
    RAYTRACER(v3);
    RAYTRACER(v4);
    RAYTRACER(v5);
    RAYTRACER(v6);
#undef RAYTRACER

    module->add(fun(&create_scene), "create_scene");

    return module;
}