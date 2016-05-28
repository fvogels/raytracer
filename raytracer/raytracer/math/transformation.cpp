#include "transformation.h"

using namespace math;

transformation math::translation(const vector3d& v)
{
	matrix4d tm = translation_matrix(v);
	matrix4d itm = translation_matrix(-v);

	return transformation(tm, itm);
}

transformation math::scale(double sx, double sy, double sz)
{
	matrix4d tm = scale_matrix(sx, sy, sz);
	matrix4d itm = scale_matrix(1 / sx, 1 / sy, 1 / sz);

	return transformation(tm, itm);
}