#pragma once

#include "materials/material.h"
#include "materials/material2d.h"
#include "materials/material3d.h"
#include "materials/uniform-material.h"
#include "materials/checkered-material.h"

namespace raytracer
{
	namespace materials
	{
		std::shared_ptr<Material> checkered(const color&, const color&);
		std::shared_ptr<Material> uniform(const color&);
	}
}