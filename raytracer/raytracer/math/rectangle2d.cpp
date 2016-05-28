#include "math/rectangle2d.h"

using namespace math;

point2d math::rectangle2d::center() const
{
	return origin + x_axis / 2 + y_axis / 2;
}

bool math::operator ==(const rectangle2d& r1, const rectangle2d& r2)
{
	return r1.origin == r2.origin && r1.x_axis == r2.x_axis && r1.y_axis == r2.y_axis;
}

bool math::operator !=(const rectangle2d& r1, const rectangle2d& r2)
{
	return !(r1 == r2);
}