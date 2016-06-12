#pragma once

#include "math/noise2d.h"
#include <memory>

namespace math
{
	std::shared_ptr<Noise2D> create_worley_noise2d();
}