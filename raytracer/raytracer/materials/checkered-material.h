#pragma once

#include "materials/material.h"

namespace raytracer
{
	class CheckeredMaterial3D : public Material3D
	{
	public:
		CheckeredMaterial3D(const color& c1, const color& c2) : c1(c1), c2(c2) { }

	protected:
		MaterialProperties at(const math::Point3D&) const override;

	private:
		color c1, c2;
	};		
}
