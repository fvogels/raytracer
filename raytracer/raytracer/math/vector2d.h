#pragma once

#include <iostream>

namespace math
{
	struct vector2d final
	{
		double x, y;

		vector2d()
			: x(0), y(0) { }

		vector2d(double x, double y)
			: x(x), y(y) { }

		vector2d(const vector2d& v) = default;

		vector2d& operator =(const vector2d&) = default;

		double dot(const vector2d&) const;

		double norm_sqr() const;
		double norm() const;
		void normalize();
		vector2d normalized() const;
		bool is_unit() const;

		vector2d& operator +=(const vector2d&);
		vector2d& operator -=(const vector2d&);
		vector2d& operator *=(double);
		vector2d& operator /=(double);
	};

	vector2d operator +(const vector2d&, const vector2d&);
	vector2d operator -(const vector2d&, const vector2d&);
	vector2d operator *(const vector2d&, double factor);
	vector2d operator *(double factor, const vector2d&);
	vector2d operator /(const vector2d&, double factor);

	std::ostream& operator <<(std::ostream& out, const vector2d&);
}