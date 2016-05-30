#pragma once

#include "materials/Material3d.h"

namespace Raytracer
{
	class UniformMaterial : public Material3D
	{
	public:
		UniformMaterial(const color& c) : c(c) { }

		color at(const math::Point3D&) const override;

	private:
		color c;
	};
}