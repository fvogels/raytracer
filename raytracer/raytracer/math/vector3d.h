#pragma once

#include <iostream>

namespace math
{
	struct Vector3D final
	{
		double x, y, z;

		Vector3D()
			: x(0), y(0), z(0) { }

		Vector3D(double x, double y, double z)
			: x(x), y(y), z(z) { }

		Vector3D(const Vector3D& v) = default;

		Vector3D& operator =(const Vector3D&) = default;

		double dot(const Vector3D&) const;
		Vector3D cross(const Vector3D&) const;

		double norm_sqr() const;
		double norm() const;
		void normalize();
		Vector3D normalized() const;
		bool is_unit() const;

		Vector3D& operator +=(const Vector3D&);
		Vector3D& operator -=(const Vector3D&);
		Vector3D& operator *=(double);
		Vector3D& operator /=(double);

		bool is_perpendicular_on(const Vector3D&) const;
	};

	Vector3D operator +(const Vector3D&, const Vector3D&);
	Vector3D operator -(const Vector3D&);
	Vector3D operator -(const Vector3D&, const Vector3D&);
	Vector3D operator *(const Vector3D&, double factor);
	Vector3D operator *(double factor, const Vector3D&);
	Vector3D operator /(const Vector3D&, double factor);

	bool operator ==(const Vector3D&, const Vector3D&);
	bool operator !=(const Vector3D&, const Vector3D&);

	std::ostream& operator <<(std::ostream& out, const Vector3D&);
}