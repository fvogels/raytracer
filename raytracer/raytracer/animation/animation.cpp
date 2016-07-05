#include "animation/animation.h"
#include <functional>

using namespace animation;
using namespace math;

Animation<math::Point3D> animation::circular_xz(double radius, const math::Interval<math::Angle>& angle_interval, const math::Interval<TimeStamp>& time_interval)
{
    std::function<Point3D(TimeStamp)> lambda = [radius, angle_interval, time_interval](TimeStamp ts)
    {
        double t = time_interval.to_relative(ts);
        Angle angle = angle_interval.from_relative(t);

        return Point3D::in_xz_plane(radius, angle);
    };

    return Animation<Point3D>(from_lambda(lambda), time_interval);
}
