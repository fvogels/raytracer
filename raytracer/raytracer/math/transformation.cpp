#include "transformation.h"

using namespace math;

transformation math::translation(const vector3d& v)
{
	Matrix4D tm = translation_matrix(v);
	Matrix4D itm = translation_matrix(-v);

	return transformation(tm, itm);
}

transformation math::scale(double sx, double sy, double sz)
{
	Matrix4D tm = scale_matrix(sx, sy, sz);
	Matrix4D itm = scale_matrix(1 / sx, 1 / sy, 1 / sz);

	return transformation(tm, itm);
}