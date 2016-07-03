#include "animation/animation.h"

using namespace animation;
using namespace math;


double animation::Animation::duration() const
{
    return m_duration;
}

Animation<Point3D> animation::rotate_around(const Point3D&, double radius, const Interval<math::Angle> angle)
{

}