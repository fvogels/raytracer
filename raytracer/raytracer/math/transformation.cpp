#include "Transformation.h"

using namespace math;

Transformation math::translation(const Vector3D& v)
{
	Matrix4D tm = translation_matrix(v);
	Matrix4D itm = translation_matrix(-v);

	return Transformation(tm, itm);
}

Transformation math::scale(double sx, double sy, double sz)
{
	Matrix4D tm = scale_matrix(sx, sy, sz);
	Matrix4D itm = scale_matrix(1 / sx, 1 / sy, 1 / sz);

	return Transformation(tm, itm);
}