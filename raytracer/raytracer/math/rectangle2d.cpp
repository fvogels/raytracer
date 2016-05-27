#include "math/rectangle2d.h"

using namespace math;

point2d math::rectangle2d::center() const
{
	return origin + x_axis / 2 + y_axis / 2;
}