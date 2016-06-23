#include "primitives/primitives.h"
#include "primitives/primitive.h"
#include "primitives/plane.h"
#include "primitives/sphere.h"
#include "primitives/cylinder.h"
#include "primitives/union.h"
#include "primitives/transformer.h"
#include "primitives/decorator.h"
#include "math/transformation.h"

using namespace raytracer;
using namespace raytracer::primitives;

std::shared_ptr<Primitive> raytracer::primitives::xy_plane()
{
	return std::make_shared<raytracer::primitives::PlaneXY>();
}

std::shared_ptr<Primitive> raytracer::primitives::xz_plane()
{
	return std::make_shared<raytracer::primitives::PlaneXZ>();
}

std::shared_ptr<Primitive> raytracer::primitives::yz_plane()
{
	return std::make_shared<raytracer::primitives::PlaneYZ>();
}

std::shared_ptr<Primitive> raytracer::primitives::sphere()
{
	return std::make_shared<raytracer::primitives::Sphere>();
}

std::shared_ptr<Primitive> raytracer::primitives::cylinder()
{
	return std::make_shared<raytracer::primitives::Cylinder>();
}

std::shared_ptr<Primitive> raytracer::primitives::transform(const math::Transformation& transformation, std::shared_ptr<const Primitive> transformee)
{
	return std::make_shared<Transformer>(transformation, transformee);
}

std::shared_ptr<Primitive> raytracer::primitives::translate(const math::Vector3D& v, std::shared_ptr<const Primitive> transformee)
{
	return transform(math::translation(v), transformee);
}

std::shared_ptr<Primitive> raytracer::primitives::scale(double x, double y, double z, std::shared_ptr<const Primitive> transformee)
{
	return transform(math::scale(x, y, z), transformee);
}

std::shared_ptr<Primitive> raytracer::primitives::rotate_around_x(math::Angle angle, std::shared_ptr<const Primitive> transformee)
{
	return transform(math::rotate_x(angle), transformee);
}

std::shared_ptr<Primitive> raytracer::primitives::rotate_around_y(math::Angle angle, std::shared_ptr<const Primitive> transformee)
{
	return transform(math::rotate_y(angle), transformee);
}

std::shared_ptr<Primitive> raytracer::primitives::rotate_around_z(math::Angle angle, std::shared_ptr<const Primitive> transformee)
{
	return transform(math::rotate_z(angle), transformee);
}

std::shared_ptr<Primitive> raytracer::primitives::decorate(Material material, std::shared_ptr<Primitive> child)
{
	return std::make_shared<raytracer::primitives::Decorator>(material, child);
}

std::shared_ptr<Primitive> raytracer::primitives::group(std::vector<std::shared_ptr<Primitive>>& children)
{
	return std::make_shared<raytracer::primitives::Union>(children);
}