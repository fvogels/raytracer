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

        Camera perspective_by_map(const std::map<std::string, Boxed_Value> argument_map) const
        {
            START_ARGUMENTS(argument_map);
            ARGUMENT(Point3D, eye);
            ARGUMENT(Point3D, look_at);
            ARGUMENT(Vector3D, up);
            ARGUMENT(double, distance);
            ARGUMENT(double, aspect_ratio);
            END_ARGUMENTS();

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

        Camera orthographic_by_map(const std::map<std::string, Boxed_Value> argument_map) const
        {
            START_ARGUMENTS(argument_map);
            ARGUMENT(Point3D, eye);
            ARGUMENT(Point3D, look_at);
            ARGUMENT(Vector3D, up);
            ARGUMENT(double, window_width);
            ARGUMENT(double, aspect_ratio);
            END_ARGUMENTS();

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

        Camera fisheye_by_map(const std::map<std::string, Boxed_Value> argument_map) const
        {
            START_ARGUMENTS(argument_map);
            ARGUMENT(Point3D, eye);
            ARGUMENT(Point3D, look_at);
            ARGUMENT(Vector3D, up);
            ARGUMENT(double, horizontal_angle);
            ARGUMENT(double, vertical_angle);
            END_ARGUMENTS();

            return cameras::fisheye(eye, look_at, up, Angle::degrees(horizontal_angle), Angle::degrees(vertical_angle));
        }

        Camera depth_of_field(
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

        Camera depth_of_field_by_map(const std::map<std::string, Boxed_Value> argument_map) const
        {
            START_ARGUMENTS(argument_map);
            ARGUMENT(Point3D, eye);
            ARGUMENT(Point3D, look_at);
            ARGUMENT(Vector3D, up);
            ARGUMENT(double, distance);
            ARGUMENT(double, aspect_ratio);
            ARGUMENT(double, eye_size);
            ARGUMENT(Sampler, eye_sampler);
            END_ARGUMENTS();

            return cameras::depth_of_field_perspective(eye, look_at, up, distance, aspect_ratio, eye_size, eye_sampler);
        }
    };
}

ModulePtr raytracer::scripting::_private_::create_cameras_module()
{
    auto module = std::make_shared<chaiscript::Module>();

    util::register_type<Camera>(*module, "Camera");

    auto camera_library = std::make_shared<CameraLibrary>();
    module->add_global_const(chaiscript::const_var(camera_library), "Cameras");

#define CAMERA(NAME) module->add(fun(&CameraLibrary::NAME), #NAME); module->add(fun(&CameraLibrary::NAME ## _by_map), #NAME)
    CAMERA(perspective);
    CAMERA(orthographic);
    CAMERA(fisheye);
    CAMERA(depth_of_field);
#undef CAMERA

    return module;
}