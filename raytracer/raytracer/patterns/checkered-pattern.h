#pragma once

#include "patterns/pattern.h"
#include "math/point.h"


namespace patterns
{
    Pattern2D checkered(double xthickness, double ythickness);
    Pattern2D wrong_checkered(double xthickness, double ythickness);
    Pattern3D checkered(double xthickness, double ythickness, double zthickness);
}
