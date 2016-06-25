#pragma once

#include "materials/material.h"

namespace raytracer
{
	class UniformMaterial : public Material3D
	{
	public:
		UniformMaterial(const imaging::color& diffuse)
			: m_diffuse(diffuse) { }

	protected:
		MaterialProperties at(const math::Point3D&) const override;

	private:
		imaging::color m_diffuse;
	};
}