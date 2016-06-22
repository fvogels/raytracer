#pragma once

#include "math/util.h"
#include <iostream>


namespace math
{
	struct Vector3D final
	{
		double x, y, z;

		constexpr Vector3D() noexcept
			: x(0), y(0), z(0) { }

		constexpr Vector3D(double x, double y, double z) noexcept
			: x(x), y(y), z(z) { }

		constexpr Vector3D(const Vector3D& v) noexcept = default;

		Vector3D& operator =(const Vector3D&) noexcept = default;

		constexpr double dot(const Vector3D&) const noexcept;
		Vector3D cross(const Vector3D&) const noexcept;

		constexpr double norm_sqr() const noexcept;
		double norm() const noexcept;
		void normalize() noexcept;
		Vector3D normalized() const noexcept;
		bool is_unit() const noexcept;

		Vector3D& operator +=(const Vector3D&) noexcept;
		Vector3D& operator -=(const Vector3D&) noexcept;
		Vector3D& operator *=(double) noexcept;
		Vector3D& operator /=(double) noexcept;

		constexpr bool is_perpendicular_on(const Vector3D& v) const noexcept
		{
			return dot(v) == approx(0);
		}
	};

	constexpr Vector3D operator +(const Vector3D& u, const Vector3D& v) noexcept
	{
		return Vector3D(u.x + v.x, u.y + v.y, u.z + v.z);
	}

	constexpr Vector3D operator -(const Vector3D& v) noexcept
	{
		return Vector3D(-v.x, -v.y, -v.z);
	}

	constexpr Vector3D operator -(const Vector3D& u, const Vector3D& v) noexcept
	{
		return Vector3D(u.x - v.x, u.y - v.y, u.z - v.z);
	}

	constexpr Vector3D operator *(const Vector3D& v, double factor) noexcept
	{
		return Vector3D(v.x * factor, v.y * factor, v.z * factor);
	}

	constexpr Vector3D operator *(double factor, const Vector3D& v) noexcept
	{
		return v * factor;
	}

	constexpr Vector3D operator /(const Vector3D& v, double factor) noexcept
	{
		return v * (1.0 / factor);
	}

	constexpr bool operator ==(const Vector3D& u, const Vector3D& v) noexcept
	{
		return u.x == v.x && u.y == v.y && u.z == v.z;
	}

	constexpr bool operator !=(const Vector3D& u, const Vector3D& v) noexcept
	{
		return !(u == v);
	}

	std::ostream& operator <<(std::ostream& out, const Vector3D&);
}