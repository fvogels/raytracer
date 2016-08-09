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

template<typename T>
Animation<T> make_straight(const T& from, const T& to, const Duration& duration)
{
    auto x_animation = straight(from.x(), to.x(), duration);
    auto y_animation = straight(from.y(), to.y(), duration);
    auto z_animation = straight(from.z(), to.z(), duration);

    std::function<T(TimeStamp)> lambda = [x_animation, y_animation, z_animation](TimeStamp now) -> T {
        double x = x_animation(now);
        double y = y_animation(now);
        double z = z_animation(now);

        return T(x, y, z);
    };

    return make_animation(from_lambda(lambda), duration);
}

Animation<Point3D> animation::straight(const Point3D& from, const Point3D& to, const Duration& duration)
{
    return make_straight<Point3D>(from, to, duration);
}

Animation<Vector3D> animation::straight(const Vector3D& from, const Vector3D& to, const Duration& duration)
{
    return make_straight<Vector3D>(from, to, duration);
}

