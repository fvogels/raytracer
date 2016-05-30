#include "math/rectangle2D.h"

using namespace math;

Point2D math::Rectangle2D::center() const
{
	return origin + x_axis / 2 + y_axis / 2;
}

bool math::operator ==(const Rectangle2D& r1, const Rectangle2D& r2)
{
	return r1.origin == r2.origin && r1.x_axis == r2.x_axis && r1.y_axis == r2.y_axis;
}

bool math::operator !=(const Rectangle2D& r1, const Rectangle2D& r2)
{
	return !(r1 == r2);
}