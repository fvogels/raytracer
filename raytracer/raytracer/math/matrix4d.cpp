#include "math/Matrix4d.h"

using namespace math;

Matrix4D math::operator *(const Matrix4D& a, const Matrix4D& b)
{
#define AUX(row, col) a.x ## row ## 1 * b.x1 ## col + a.x ## row ## 2 * b.x2 ## col + a.x ## row ## 3 * b.x3 ## col + a.x ## row ## 4 * b.x4 ## col

	return Matrix4D{
		AUX(1, 1),
		AUX(1, 2),
		AUX(1, 3),
		AUX(1, 4),
		AUX(2, 1),
		AUX(2, 2),
		AUX(2, 3),
		AUX(2, 4),
		AUX(3, 1),
		AUX(3, 2),
		AUX(3, 3),
		AUX(3, 4),
		AUX(4, 1),
		AUX(4, 2),
		AUX(4, 3),
		AUX(4, 4),
	};

#undef AUX
}

vector3d math::operator *(const Matrix4D& a, const vector3d& v)
{
#define AUX(row) a.x ## row ## 1 * v.x + a.x ## row ## 2 * v.y + a.x ## row ## 3 * v.z

	return vector3d{ AUX(1), AUX(2), AUX(3) };

#undef AUX
}

Point3D math::operator *(const Matrix4D& a, const Point3D& p)
{
#define AUX(row) a.x ## row ## 1 * p.x + a.x ## row ## 2 * p.y + a.x ## row ## 3 * p.z + a.x ## row ## 4

	double x = AUX(1);
	double y = AUX(2);
	double z = AUX(3);

	return Point3D{ x, y, z };

#undef AUX
}

Matrix4D math::identity_matrix()
{
	return Matrix4D{
		1, 0 ,0 , 0,
		0, 1, 0, 0,
		0, 0, 1, 0,
		0, 0, 0, 1
	};
}

Matrix4D math::translation_matrix(const vector3d& v)
{
	return Matrix4D{
		1, 0 ,0 , v.x,
		0, 1, 0, v.y,
		0, 0, 1, v.z,
		0, 0, 0, 1
	};
}

Matrix4D math::scale_matrix(double sx, double sy, double sz)
{
	return Matrix4D{
		sx, 0 ,0 , 0,
		0, sy, 0, 0,
		0, 0, sz, 0,
		0, 0, 0, 1
	};
}