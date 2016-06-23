#pragma once

#include "imaging/color.h"
#include "math/point2d.h"
#include "primitives/hit-position.h"

namespace raytracer
{
	struct MaterialProperties
	{
		color c;
	};

	class Material
	{
	public:
		virtual MaterialProperties at(const HitPosition&) const = 0;
	};

	class Material2D : public Material
	{
	public:
		MaterialProperties at(const HitPosition&) const override;

	protected:
		virtual MaterialProperties at(const math::Point2D&) const = 0;
	};

	class Material3D : public Material
	{
	public:
		MaterialProperties at(const HitPosition&) const override;

	protected:
		virtual MaterialProperties at(const math::Point3D&) const = 0;
	};
}