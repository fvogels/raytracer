#pragma once

#include "materials/material.h"

namespace raytracer
{
	namespace materials
	{
		class UniformMaterial : public MaterialImplementation
		{
		public:
			UniformMaterial(const imaging::color& diffuse)
				: m_diffuse(diffuse) { }

			MaterialProperties at(const HitPosition&) const override;

		private:
			imaging::color m_diffuse;
		};
	}
}