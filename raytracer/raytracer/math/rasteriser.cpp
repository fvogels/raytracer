#include "math/rasteriser.h"

using namespace math;

rectangle math::rasteriser::operator [](const position& pos) const
{
	vector3d x_axis = this->rect.x_axis / this->horizontal_subdivisions;
	vector3d y_axis = this->rect.y_axis / this->vertical_subdivisions;
	point3d origin = this->rect.origin + pos.x * x_axis + pos.y * y_axis;

	return rectangle(origin, x_axis, y_axis);
}