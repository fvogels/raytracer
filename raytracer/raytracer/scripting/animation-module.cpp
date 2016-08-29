#ifndef EXCLUDE_SCRIPTING

#include "scripting/animation-module.h"
#include "scripting/scripting-util.h"
#include "raytracers/scene.h"
#include "animation/animations.h"
#include "animation/redimensioner.h"
#include "math/angle.h"


using namespace chaiscript;
using namespace raytracer;
using namespace math;
using namespace imaging;
using namespace animation;


namespace
{
    struct AnimationLibrary
    {
        Animation<Point3D> circular(
            const math::Point3D& point,
            const math::Point3D& center,
            const math::Vector3D& rotation_axis,
            const math::Interval<math::Angle>& angle_interval,
            const Duration& duration) const
        {
            return animation::circular(point, center, rotation_axis, angle_interval, duration);
        }

        Animation<Point3D> circular_by_map(const std::map<std::string, Boxed_Value>& argument_map) const
        {
            Duration duration = Duration::zero();

            START_ARGUMENTS(argument_map);
            ARGUMENT(Point3D, position);
            ARGUMENT(Point3D, around);
            OPTIONAL_ARGUMENT(Vector3D, axis, Vector3D(0, 1, 0));
            OPTIONAL_ARGUMENT(math::Interval<math::Angle>, angle_interval, math::interval(0_degrees, 360_degrees));
            BIND_ARGUMENT(duration);
            END_ARGUMENTS();

            return circular(position, around, axis, angle_interval, duration);
        }

        Animation<Point3D> point_animation(const Point3D& from, const Point3D& to, Duration duration) const
        {
            return animation::animate(from, to, duration);
        }

        Animation<Point3D> animation_seq(const std::vector<Boxed_Value>& boxed_checkpoints, Duration duration) const
        {
            if (boxed_checkpoints.size() < 2)
            {
                LOG(ERROR) << "At least 2 checkpoints needed";
                abort();
            }
            else if ( *boxed_checkpoints.front().get_type_info().bare_type_info() == typeid(Point3D) )
            {
                std::vector<Point3D> checkpoints(boxed_checkpoints.size());

                std::transform(boxed_checkpoints.begin(), boxed_checkpoints.end(), checkpoints.begin(), [](Boxed_Value boxed) {
                    return boxed_cast<Point3D>(boxed);
                });

                Animation<Point3D> animation = Animation<Point3D>::empty();

                for (size_t i = 0; i < checkpoints.size() - 1; ++i)
                {
                    auto anim = animation::animate(checkpoints[i], checkpoints[i + 1], duration / double(checkpoints.size() - 1));

                    animation = sequence(animation, ease(anim, math::functions::easing::easing_function<math::functions::easing::quadratic, math::functions::easing::inout>()));
                }

                return animation;
            }
            else
            {
                LOG(ERROR) << "Unsupported type for animation: " << boxed_checkpoints.front().get_type_info().name();
                abort();
            }
        }

        Animation<double> double_animation(double from, double to, Duration duration) const
        {
            return animation::animate(from, to, duration);
        }

        Animation<Angle> angle_animation(Angle from, Angle to, Duration duration) const
        {
            return animation::animate(from, to, duration);
        }

        Animation<Point3D> lissajous_by_map(const std::map<std::string, Boxed_Value>& argument_map) const
        {
            Duration duration = Duration::zero();

            START_ARGUMENTS(argument_map);
            OPTIONAL_ARGUMENT(double, x_amplitude, 0);
            OPTIONAL_ARGUMENT(double, x_frequency, 0);
            OPTIONAL_ARGUMENT(Angle, x_phase, 0_degrees);
            OPTIONAL_ARGUMENT(double, y_amplitude, 0);
            OPTIONAL_ARGUMENT(double, y_frequency, 0);
            OPTIONAL_ARGUMENT(Angle, y_phase, 0_degrees);
            OPTIONAL_ARGUMENT(double, z_amplitude, 0);
            OPTIONAL_ARGUMENT(double, z_frequency, 0);
            OPTIONAL_ARGUMENT(Angle, z_phase, 0_degrees);
            BIND_ARGUMENT(duration);
            END_ARGUMENTS();

            return animation::lissajous(
                LissajousParameters{ x_amplitude, x_frequency, x_phase },
                LissajousParameters{ y_amplitude, y_frequency, y_phase },
                LissajousParameters{ z_amplitude, z_frequency, z_phase }, duration);
        }

        Animation<double> cyclic_double(double from, double to, Duration duration) const
        {
            auto forward = animation::animate(from, to, duration / 2);
            auto backward = invert(forward);
            auto forward_backward = sequence(forward, backward);

            return loop(forward_backward);
        }
    };

    Duration seconds(double s)
    {
        return Duration::from_seconds(s);
    }

    Animation<std::shared_ptr<Scene>> make_scene_animation(std::function<std::shared_ptr<Scene>(TimeStamp)> function, Duration duration)
    {
        return Animation<std::shared_ptr<Scene>>(from_lambda(function), duration);
    }

    template<typename T>
    Function<T(const math::Point2D&)> redim_xyz_to_xyt(math::Function<T(const math::Point3D&)> function, TimeStamp now)
    {
        return animation::xyz_to_xyt(function)(now);
    }
}

ModulePtr raytracer::scripting::_private_::create_animation_module()
{
    auto module = std::make_shared<chaiscript::Module>();

    util::register_to_string<Duration>(*module);
    util::register_to_string<TimeStamp>(*module);

    auto animation_library = std::make_shared<AnimationLibrary>();
    module->add_global_const(chaiscript::const_var(animation_library), "Animations");

#define BIND_AS(INTERNAL, EXTERNAL)     module->add(fun(&AnimationLibrary::INTERNAL), #EXTERNAL)
#define BIND(NAME)                      BIND_AS(NAME, NAME)
    BIND(circular);
    BIND_AS(circular_by_map, circular);
    BIND_AS(double_animation, animate);
    BIND_AS(point_animation, animate);
    BIND_AS(animation_seq, animate);
    BIND_AS(angle_animation, animate);
    BIND_AS(lissajous_by_map, lissajous);
    BIND_AS(cyclic_double, cyclic);
#undef BIND
#undef BIND_AS

    module->add(fun(&redim_xyz_to_xyt<Vector3D>), "xyz_to_xyt");
    module->add(fun(&seconds), "seconds");
    module->add(fun(&Animation<Point3D>::operator()), "[]");
    module->add(fun(&Animation<Angle>::operator()), "[]");
    module->add(fun(&Animation<double>::operator()), "[]");
    module->add(fun(&make_scene_animation), "scene_animation");

    return module;
}

#endif
