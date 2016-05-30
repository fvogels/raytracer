#pragma once

#include "materials/Material3d.h"

namespace Raytracer
{
	class CheckeredMaterial : public Material3D
	{
	public:
		CheckeredMaterial(const color& c1, const color& c2) : c1(c1), c2(c2) { }

		color at(const math::Point3D&) const override;

	private:
		color c1, c2;
	};
}
