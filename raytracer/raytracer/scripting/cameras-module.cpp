#include "scripting/cameras-module.h"
#include "cameras/cameras.h"
#include "scripting/scripting-util.h"

using namespace chaiscript;
using namespace raytracer;
using namespace math;


namespace
{
    struct CameraLibrary
    {
        Camera perspective(
            const Point3D& eye,
            const Point3D& look_at,
            const Vector3D& up,
            double distance,
            double aspect_ratio) const
        {
            return cameras::perspective(eye, look_at, up, distance, aspect_ratio);
        }

        Camera orthographic(
            const Point3D& eye,
            const Point3D& look_at,
            const Vector3D& up,
            double window_width,
            double aspect_ratio) const
        {
            return cameras::orthographic(eye, look_at, up, window_width, aspect_ratio);
        }
    };

    Camera perspective(const std::map<std::string, Boxed_Value> argument_map)
    {
        EXTRACT_ARGUMENT(Point3D, eye);
        EXTRACT_ARGUMENT(Point3D, look_at);
        EXTRACT_ARGUMENT(Vector3D, up);
        EXTRACT_ARGUMENT(double, distance);
        EXTRACT_ARGUMENT(double, aspect_ratio);

        return cameras::perspective(eye, look_at, up, distance, aspect_ratio);
    }

    Camera orthographic(const std::map<std::string, Boxed_Value> argument_map)
    {
        EXTRACT_ARGUMENT(Point3D, eye);
        EXTRACT_ARGUMENT(Point3D, look_at);
        EXTRACT_ARGUMENT(Vector3D, up);
        EXTRACT_ARGUMENT(double, window_width);
        EXTRACT_ARGUMENT(double, aspect_ratio);

        return cameras::orthographic(eye, look_at, up, window_width, aspect_ratio);
    }

    Camera create_camera(const std::map<std::string, Boxed_Value> argument_map)
    {
        EXTRACT_ARGUMENT(std::string, type);

        FACTORY_TYPE_DISPATCH(perspective);
        FACTORY_TYPE_DISPATCH(orthographic);
        HANDLE_UNKNOWN_TYPE;
    }
}

ModulePtr raytracer::scripting::_private_::create_cameras_module()
{
    auto module = std::make_shared<chaiscript::Module>();

    auto camera_library = std::make_shared<CameraLibrary>();
    module->add_global_const(chaiscript::const_var(camera_library), "Cameras");

#define CAMERA(NAME) module->add(fun(&CameraLibrary::NAME), #NAME)
    CAMERA(perspective);
#undef COLOR

    module->add(fun(&create_camera), "camera");

    return module;
}