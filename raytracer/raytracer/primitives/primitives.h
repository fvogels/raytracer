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
		std::shared_ptr<Primitive> sphere();
		std::shared_ptr<Primitive> cylinder();
		std::shared_ptr<Primitive> plane(const math::Point3D&, const math::Vector3D&, const math::Vector3D&);

		std::shared_ptr<Primitive> transform(const math::Transformation&, std::shared_ptr<const Primitive>);
		std::shared_ptr<Primitive> translate(const math::Vector3D&, std::shared_ptr<const Primitive>);
		std::shared_ptr<Primitive> rotate_around_x(math::Angle, std::shared_ptr<const Primitive>);
		std::shared_ptr<Primitive> rotate_around_y(math::Angle, std::shared_ptr<const Primitive>);
		std::shared_ptr<Primitive> rotate_around_z(math::Angle, std::shared_ptr<const Primitive>);

		std::shared_ptr<Primitive> decorate(std::shared_ptr<Material> material, std::shared_ptr<Primitive> child);
		std::shared_ptr<Primitive> group(std::vector<std::shared_ptr<Primitive>>&);
	}
}