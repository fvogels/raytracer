#pragma once

#include "materials/material.h"
#include "imaging/color.h"
#include "math/point2d.h"
#include "math/function.h"
#include <memory>

namespace raytracer
{
	class Material2D : public Material
	{
	public:
		virtual color at(const math::Point2D&) const = 0;
	};

	class SimpleMaterial2D : public Material2D
	{
	public:
		SimpleMaterial2D(std::shared_ptr<math::Function<color, const math::Point2D&>> color_function)
			: m_color_function(color_function) { }

		color at(const math::Point2D& p) const override
		{
			return (*m_color_function)(p);
		}

	private:
		std::shared_ptr<math::Function<color, const math::Point2D&>> m_color_function;
	};
}