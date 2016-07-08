#include "animation/animation.h"
#include "math/quaternion.h"
#include <functional>

using namespace animation;
using namespace math;

Animation<math::Point3D> animation::circular_xz(double radius, const math::Interval<math::Angle>& angle_interval, const Duration& duration)
{
    std::function<Point3D(TimeStamp)> lambda = [radius, angle_interval, duration](TimeStamp ts)
    {
        Interval<TimeStamp> time_interval(TimeStamp::zero(), TimeStamp::from_epoch(duration));
        double t = time_interval.to_relative(ts);
        Angle angle = angle_interval.from_relative(t);

        return Point3D::in_xz_plane(radius, angle);
    };

    return Animation<Point3D>(from_lambda(lambda), duration);
}

Animation<math::Point3D> animation::circular(
    const math::Point3D& point,
    const math::Point3D& center,
    const math::Vector3D& rotation_axis,
    const math::Interval<math::Angle>& angle_interval,
    const Duration& duration)
{
    Vector3D translation = center - Point3D::origin();

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