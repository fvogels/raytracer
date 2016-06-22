#pragma once

#include "math/vector3d.h"

namespace math
{
	struct Point3D final
	{
		double x, y, z;

		constexpr Point3D() noexcept
			: x(0), y(0), z(0) { }

		constexpr Point3D(double x, double y, double z) noexcept
			: x(x), y(y), z(z) { }

		constexpr Point3D(const Point3D& v) noexcept = default;

		Point3D& operator =(const Point3D&) noexcept = default;
	};

	constexpr Point3D operator +(const Point3D& p, const Vector3D& v) noexcept
	{
		return Point3D(p.x + v.x, p.y + v.y, p.z + v.z);
	}

	constexpr Point3D operator +(const Vector3D& v, const Point3D& p) noexcept
	{
		return p + v;
	}

	constexpr Vector3D operator -(const Point3D& p, const Point3D& q) noexcept
	{
		return Vector3D(p.x - q.x, p.y - q.y, p.z - q.z);
	}

	constexpr Point3D operator -(const Point3D& p, const Vector3D& v) noexcept
	{
		return Point3D(p.x - v.x, p.y - v.y, p.z - v.z);
	}

	constexpr bool operator ==(const Point3D& p, const Point3D& q) noexcept
	{
		return p.x == q.x && p.y == q.y && p.z == q.z;
	}

	constexpr bool operator !=(const Point3D& p, const Point3D& q) noexcept
	{
		return !(p == q);
	}

	double distance(const Point3D&, const Point3D&) noexcept;

	std::ostream& operator <<(std::ostream& out, const Point3D&);
}
