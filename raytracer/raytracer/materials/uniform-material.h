#pragma once

#include "materials/material3d.h"

namespace raytracer
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