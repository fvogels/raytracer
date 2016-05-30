#include "math/rectangle3D.h"

using namespace math;

Point3D math::Rectangle3D::project(const Point2D& p) const
{
	return origin + x_axis * p.x + y_axis * p.y;
}
