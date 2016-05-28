#pragma once

#include "materials/Material3D.h"

namespace Raytracer
{
	class UniformMaterial : public Material3D
	{
	public:
		UniformMaterial(const color& c) : c(c) { }

		color at(const math::point3d&) const override;

	private:
		color c;
	};
}