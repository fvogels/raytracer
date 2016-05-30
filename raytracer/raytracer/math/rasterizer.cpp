#include "math/Rasterizer.h"

using namespace math;

Rectangle2D math::Rasterizer::operator [](const position& pos) const
{
	vector2d x_axis = this->rect.x_axis / this->horizontal_subdivisions;
	vector2d y_axis = this->rect.y_axis / this->vertical_subdivisions;
	Point2D origin = this->rect.origin + pos.x * x_axis + pos.y * y_axis;

	return Rectangle2D(origin, x_axis, y_axis);
}