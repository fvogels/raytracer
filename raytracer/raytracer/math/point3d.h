#pragma once

#include "math/vector3d.h"

namespace math
{
	struct Point3D final
	{
		double x, y, z;

		Point3D() noexcept
			: x(0), y(0), z(0) { }

		Point3D(double x, double y, double z) noexcept
			: x(x), y(y), z(z) { }

		Point3D(const Point3D& v) noexcept = default;

		Point3D& operator =(const Point3D&) noexcept = default;
	};

	Point3D operator +(const Point3D&, const Vector3D&) noexcept;
	Point3D operator +(const Vector3D&, const Point3D&) noexcept;
	Vector3D operator -(const Point3D&, const Point3D&) noexcept;
	Point3D operator -(const Point3D&, const Vector3D&) noexcept;
	bool operator ==(const Point3D&, const Point3D&) noexcept;
	bool operator !=(const Point3D&, const Point3D&) noexcept;

	double distance(const Point3D&, const Point3D&) noexcept;

	std::ostream& operator <<(std::ostream& out, const Point3D&);
}
