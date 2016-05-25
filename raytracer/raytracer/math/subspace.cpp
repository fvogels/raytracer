#include "math/subspace.h"

using namespace math;

point3d math::subspace::project(const point2d& p) const
{
	return origin + x_axis * p.x + y_axis * p.y;
}