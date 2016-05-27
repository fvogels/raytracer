#pragma once

#include <iostream>

namespace math
{
	struct vector3d final
	{
		double x, y, z;

		vector3d()
			: x(0), y(0), z(0) { }

		vector3d(double x, double y, double z)
			: x(x), y(y), z(z) { }

		vector3d(const vector3d& v) = default;

		vector3d& operator =(const vector3d&) = default;

		double dot(const vector3d&) const;
		vector3d cross(const vector3d&) const;

		double norm_sqr() const;
		double norm() const;
		void normalize();
		vector3d normalized() const;
		bool is_unit() const;

		vector3d& operator +=(const vector3d&);
		vector3d& operator -=(const vector3d&);
		vector3d& operator *=(double);
		vector3d& operator /=(double);

		bool is_perpendicular_on(const vector3d&) const;
	};

	vector3d operator +(const vector3d&, const vector3d&);
	vector3d operator -(const vector3d&);
	vector3d operator -(const vector3d&, const vector3d&);
	vector3d operator *(const vector3d&, double factor);
	vector3d operator *(double factor, const vector3d&);
	vector3d operator /(const vector3d&, double factor);

	std::ostream& operator <<(std::ostream& out, const vector3d&);
}