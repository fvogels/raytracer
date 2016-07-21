#include "scripting/cameras-module.h"
#include "cameras/cameras.h"

using namespace chaiscript;
using namespace raytracer;
using namespace math;


namespace
{
    struct CameraLibrary
    {
        Camera perspective(
            const math::Point3D& eye,
            const math::Point3D& look_at,
            const math::Vector3D& up,
            double distance,
            double aspect_ratio) const
        {
            return cameras::perspective(eye, look_at, up, distance, aspect_ratio);
        }
    };
}

ModulePtr raytracer::scripting::_private_::create_cameras_module()
{
    auto module = std::make_shared<chaiscript::Module>();

    auto camera_library = std::make_shared<CameraLibrary>();
    module->add_global_const(chaiscript::const_var(camera_library), "Cameras");

#define CAMERA(NAME) module->add(fun(&CameraLibrary::NAME), #NAME)
    CAMERA(perspective);
#undef COLOR

    return module;
}