#pragma once

#include "primitives/primitive.h"
#include "math/transformation.h"
#include "math/angle.h"
#include "math/vector3d.h"
#include "math/point3d.h"
#include <memory>
#include <vector>


namespace raytracer
{
	namespace primitives
	{
		Primitive xy_plane();
		Primitive xz_plane();
		Primitive yz_plane();
		Primitive sphere();
		Primitive cylinder();

		Primitive transform(const math::Transformation&, Primitive);
		Primitive translate(const math::Vector3D&, Primitive);
		Primitive scale(double x, double y, double z, Primitive);
		Primitive rotate_around_x(math::Angle, Primitive);
		Primitive rotate_around_y(math::Angle, Primitive);
		Primitive rotate_around_z(math::Angle, Primitive);

		Primitive decorate(Material material, Primitive child);
		Primitive group(std::vector<Primitive>&);
		Primitive intersection(Primitive, Primitive);
	}
}