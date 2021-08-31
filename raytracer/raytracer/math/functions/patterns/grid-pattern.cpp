#include "math/functions/patterns/grid-pattern.h"
#include "math/functions/patterns/lines-pattern.h"
#include "math/functions/patterns/lambda-pattern.h"
#include "math/functions/patterns/pattern-operations.h"
#include <cmath>


using namespace math::functions;


Pattern2D math::functions::patterns::grid(double xthickness, double ythickness, double xspacing, double yspacing, math::Angle angle)
{
    auto hline = math::functions::patterns::lines(xthickness, xspacing, 0_degrees);
    auto vline = math::functions::patterns::lines(ythickness, yspacing, 90_degrees);

    return rotate(angle, disjunction(hline, vline));
}
