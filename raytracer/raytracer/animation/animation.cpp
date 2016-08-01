#include "animation/animation.h"
#include "math/quaternion.h"
#include <functional>

using namespace animation;
using namespace math;


Animation<double> animation::straight(double from, double to, const Duration& duration)
{
    Interval<double> position_interval(from, to);
    Interval<TimeStamp> time_interval(TimeStamp::zero(), TimeStamp::from_epoch(duration));

    std::function<double(TimeStamp)> lambda = [position_interval, time_interval](TimeStamp now) -> double {
        double t = time_interval.to_relative(now);
        return position_interval.from_relative(t);
    };

    return make_animation(from_lambda(lambda), duration);
}

Animation<Point3D> animation::straight(const Point3D& from, const Point3D& to, const Duration& duration)
{
    auto x_animation = straight(from.x(), to.x(), duration);
    auto y_animation = straight(from.y(), to.y(), duration);
    auto z_animation = straight(from.z(), to.z(), duration);

    std::function<Point3D(TimeStamp)> lambda = [x_animation, y_animation, z_animation](TimeStamp now) -> Point3D {
        double x = x_animation(now);
        double y = y_animation(now);
        double z = z_animation(now);

        return Point3D(x, y, z);
    };

    return make_animation(from_lambda(lambda), duration);
}

Animation<math::Point3D> animation::circular(
    const math::Point3D& point,
    const math::Point3D& center,
    const math::Vector3D& rotation_axis,
    const math::Interval<math::Angle>& angle_interval,
    const Duration& duration)
{
    Vector3D translation = center - math::Point3D(0.0, 0.0, 0.0);

    std::function<Point3D(TimeStamp)> lambda = [point, translation, rotation_axis, angle_interval, duration](TimeStamp ts)
    {
        Interval<TimeStamp> time_interval(TimeStamp::zero(), TimeStamp::from_epoch(duration));
        double t = time_interval.to_relative(ts);
        Angle angle = angle_interval.from_relative(t);
        Quaternion q(angle, rotation_axis);
        Point3D result = q.rotate(point - translation) + translation;

        return result;
    };

    return Animation<Point3D>(from_lambda(lambda), duration);
}