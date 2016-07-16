#include "chai/raytracing-module.h"
#include "raytracing/ray-tracers.h"

using namespace chaiscript;
using namespace raytracer;


namespace
{
    struct RaytracerLibrary
    {
        RayTracer binary() const { return raytracer::raytracers::binary(); }
    };
}

ModulePtr raytracer::scripting::_private_::create_raytracing_module()
{
    auto module = std::make_shared<chaiscript::Module>();

    auto raytracer_library = std::make_shared<RaytracerLibrary>();
    module->add_global_const(chaiscript::const_var(raytracer_library), "Raytracers");

#define RAYTRACER(NAME) module->add(fun(&RaytracerLibrary::NAME), #NAME)
    RAYTRACER(binary);
#undef COLOR

    module->add(user_type<Scene>(), "Scene");
    module->add(constructor<Scene(raytracer::Camera, raytracer::Primitive)>(), "Scene");
    module->add(fun([](Scene& scene, LightSource light) { scene.light_sources.push_back(light); }), "add_light");

    return module;
}