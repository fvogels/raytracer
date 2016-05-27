#include "math/matrix4d.h"

using namespace math;

matrix4d math::translation_matrix(const vector3d& v)
{
	return matrix4d {
		1, 0 ,0 , v.x,
		0, 1, 0, v.y,
		0, 0, 1, v.z,
		0, 0, 0, 1
	};
}