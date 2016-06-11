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

	Point3D operator +(const Point3D&, const Vector3D&);
	Point3D operator +(const Vector3D&, const Point3D&);
	Vector3D operator -(const Point3D&, const Point3D&);
	Point3D operator -(const Point3D&, const Vector3D&);

	bool operator ==(const Point3D&, const Point3D&);
	bool operator !=(const Point3D&, const Point3D&);

	double distance(const Point3D&, const Point3D&);

	std::ostream& operator <<(std::ostream& out, const Point3D&);
}
