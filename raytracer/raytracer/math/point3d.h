#pragma once

#include "math/vector3d.h"

namespace math
{
	struct Point3D final
	{
		double x, y, z;

		Point3D()
			: x(0), y(0), z(0) { }

		Point3D(double x, double y, double z)
			: x(x), y(y), z(z) { }

		Point3D(const Point3D& v) = default;

		Point3D& operator =(const Point3D&) = default;
	};

	Point3D operator +(const Point3D&, const vector3d&);
	Point3D operator +(const vector3d&, const Point3D&);
	vector3d operator -(const Point3D&, const Point3D&);
	Point3D operator -(const Point3D&, const vector3d&);

	double distance(const Point3D&, const Point3D&);
}
