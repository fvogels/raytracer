#include "math/rectangle3d.h"

using namespace math;

Point3D math::rectangle3d::project(const Point2D& p) const
{
	return origin + x_axis * p.x + y_axis * p.y;
}
