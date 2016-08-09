#include "scripting/animation-module.h"
#include "scripting/scripting-util.h"
#include "raytracing/scene.h"
#include "animation/animations.h"
#include "animation/redimensioner.h"
#include "imaging/color.h"

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

        Animation<Point3D> point_animation(const Point3D& from, const Point3D& to, const Duration& duration) const
        {
            return animation::interval(from, to, duration);
        }

        Animation<double> double_animation(double from, double to, Duration duration) const
        {
            return animation::interval(from, to, duration);
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

    auto animation_library = std::make_shared<AnimationLibrary>();
    module->add_global_const(chaiscript::const_var(animation_library), "Animations");

#define BIND_AS(INTERNAL, EXTERNAL)     module->add(fun(&AnimationLibrary::INTERNAL), #EXTERNAL)
#define BIND(NAME)                      BIND_AS(NAME, NAME)
    BIND(circular);
    BIND(point_animation);
    BIND(double_animation);
    BIND_AS(point_animation, animate);
#undef BIND
#undef BIND_AS

    module->add(fun(&redim_xyz_to_xyt<Vector3D>), "xyz_to_xyt");
    module->add(fun(&seconds), "seconds");
    module->add(fun(&Animation<Point3D>::operator()), "[]");
    module->add(fun(&make_scene_animation), "scene_animation");

    return module;
}
