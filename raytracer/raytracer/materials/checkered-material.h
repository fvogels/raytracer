#pragma once

#include "materials/material2d.h"
#include "materials/material3d.h"

namespace raytracer
{
	class CheckeredMaterial2D : public Material2D
	{
	public:
		CheckeredMaterial2D(const color& c1, const color& c2) : c1(c1), c2(c2) { }

		color at(const math::Point2D&) const override;

	private:
		color c1, c2;
	};

	class CheckeredMaterial3D : public Material3D
	{
	public:
		CheckeredMaterial3D(const color& c1, const color& c2) : c1(c1), c2(c2) { }

		color at(const math::Point3D&) const override;

	private:
		color c1, c2;
	};		
}
