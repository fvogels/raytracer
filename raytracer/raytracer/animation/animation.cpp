#include "animation/animation.h"
#include <functional>

using namespace animation;
using namespace math;

//
//Animation<math::Point3D> animation::circular_xz(Angle start, Angle end, Duration duration)
//{
//    std::function<Point3D(TimeStamp)> lambda = [start, end, duration](TimeStamp ts)
//    {
//        double 
//        return Point3D(cos(start + (end - start) * ts.seconds()), 0, sin(start + (end - start) * ts.seconds()));
//    };
//
//    return Animation(from_lambda(lambda), );
//}

//Animation<math::Point3D> animation::circular_xz(const math::Point3D& around, double radius, Angle start, Angle end, const Duration& duration)
//{
//    std::function<Point3D(TimeStamp)> function = [around, radius, start, end, duration](TimeStamp ts)
//    {
//        return around + Point3D(radius * cos(a
//    };
//}