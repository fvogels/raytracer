#pragma once

#include "materials/material.h"

namespace raytracer
{
	class UniformMaterial : public Material3D
	{
	public:
		UniformMaterial(const imaging::color& c) : c(c) { }

	protected:
		MaterialProperties at(const math::Point3D&) const override;

	private:
		imaging::color c;
	};
}