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

        Camera fisheye(
            const Point3D& eye,
            const Point3D& look_at,
            const Vector3D& up,
            double horizontal_angle,
            double vertical_angle) const
        {
            return cameras::orthographic(eye, look_at, up, horizontal_angle, vertical_angle);
        }

        Camera depth_of_field_perspective(
            const math::Point3D& eye,
            const math::Point3D& look_at,
            const math::Vector3D& up,
            double distance,
            double aspect_ratio,
            double eye_size,
            raytracer::Sampler eye_sampler) const
        {
            return cameras::depth_of_field_perspective(eye, look_at, up, distance, aspect_ratio, eye_size, eye_sampler);
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

    Camera fisheye(const std::map<std::string, Boxed_Value> argument_map)
    {
        EXTRACT_ARGUMENT(Point3D, eye);
        EXTRACT_ARGUMENT(Point3D, look_at);
        EXTRACT_ARGUMENT(Vector3D, up);
        EXTRACT_ARGUMENT(double, horizontal_angle);
        EXTRACT_ARGUMENT(double, vertical_angle);

        return cameras::fisheye(eye, look_at, up, Angle::degrees(horizontal_angle), Angle::degrees(vertical_angle));
    }

    Camera depth_of_field_perspective(const std::map<std::string, Boxed_Value> argument_map)
    {
        EXTRACT_ARGUMENT(Point3D, eye);
        EXTRACT_ARGUMENT(Point3D, look_at);
        EXTRACT_ARGUMENT(Vector3D, up);
        EXTRACT_ARGUMENT(double, distance);
        EXTRACT_ARGUMENT(double, aspect_ratio);
        EXTRACT_ARGUMENT(double, eye_size);
        EXTRACT_ARGUMENT(Sampler, eye_sampler);

        return cameras::depth_of_field_perspective(eye, look_at, up, distance, aspect_ratio, eye_size, eye_sampler);
    }

    Camera create_camera(const std::map<std::string, Boxed_Value> argument_map)
    {
        EXTRACT_ARGUMENT(std::string, type);

        FACTORY_TYPE_DISPATCH(perspective);
        FACTORY_TYPE_DISPATCH(orthographic);
        FACTORY_TYPE_DISPATCH(fisheye);
        FACTORY_TYPE_DISPATCH(depth_of_field_perspective);
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