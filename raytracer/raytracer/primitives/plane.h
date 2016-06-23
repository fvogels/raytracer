#pragma once

#include "primitives/primitive.h"

namespace raytracer
{
	namespace primitives
	{
		class CoordinatePlane : public Primitive
		{
		public:
			std::vector<std::shared_ptr<Hit>> hits(const math::Ray&) const override;
		};

		class PlaneXY : public CoordinatePlane
		{
		public:
			bool find_hit(const math::Ray&, Hit*) const override;
		};

		class PlaneXZ : public CoordinatePlane
		{
		public:
			bool find_hit(const math::Ray&, Hit*) const override;
		};

		class PlaneYZ : public CoordinatePlane
		{
		public:
			bool find_hit(const math::Ray&, Hit*) const override;
		};
	}
}