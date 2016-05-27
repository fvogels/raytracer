#include "transformation.h"

using namespace math;

transformation math::translation(const vector3d& v)
{
	matrix4d tm = translation_matrix(v);
	matrix4d itm = translation_matrix(-v);

	return transformation(tm, itm);
}