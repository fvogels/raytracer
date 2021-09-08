#pragma once

#include "patterns/pattern.h"
#include "math/point.h"
#include "math/transformation2d.h"
#include "math/transformation3d.h"
#include <memory>


namespace patterns
{
    Pattern2D tessellate(Pattern2D pattern, double width, double height);
    Pattern2D wrong_tessellate(Pattern2D pattern, double width, double height);
    Pattern2D tessellate_x(Pattern2D pattern, double width);
    Pattern2D tessellate_y(Pattern2D pattern, double height);

    Pattern3D tessellate(Pattern3D pattern, double x_size, double y_size, double z_size);
}
